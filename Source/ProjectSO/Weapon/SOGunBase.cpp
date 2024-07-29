// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGunBase.h"

#include "KisMet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/CapsuleComponent.h"

#include "SOProjectileBase.h"
#include "ProjectSO/Character/SOCharacterBase.h"
#include "Projectile/SOProjectilePoolComponent.h"
#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Core/SOGameSubsystem.h"

// Sets default values
ASOGunBase::ASOGunBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetVisibility(true, false);	
	//WeaponMesh->SetMobility(EComponentMobility::Movable);
	WeaponMesh->SetSimulatePhysics(true);
	//WeaponMesh->SetupAttachment(CollisionComp);
	RootComponent = WeaponMesh;
	
	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	CollisionComp->InitCapsuleSize(40.0f, 50.0f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetMobility(EComponentMobility::Movable);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComp->SetupAttachment(RootComponent);

	//RootComponent = CollisionComp;

	ProjectilePoolComponent = CreateDefaultSubobject<USOProjectilePoolComponent>(TEXT("ProjectilePool"));
	
	// 초기 CurrentFireMode 설정
	CurrentFireMode = ESOFireMode::None;
	
	CurrentAmmoInClip = 30;

	MaxRange = 1000;
	MuzzleSocketName = "MuzzleSocket";
	MaxRepeatCount = 3;
	AvailableFireMode = static_cast<int32>(ESOFireMode::None);
}

// Called when the game starts or when spawned
void ASOGunBase::BeginPlay()
{
	Super::BeginPlay();

	//Gun Data Setting
	SetGunData(WeaponID);

	//Object Pool
	ProjectilePoolComponent->Initialize();
	
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASOGunBase::OnSphereBeginOverlap);
	
	//여기서 타이머
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASOGunBase::DisablePhysics, 2.0f, false);

	AvailableFireModeCount = CalculateAvailableFireModeCount();
	SO_LOG(LogSOTemp,Warning, TEXT("AvailableFireMode : %d"), AvailableFireMode)

	InitCurrentFireMode();
}

// Called every frame
void ASOGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASOGunBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASOGunBase, OwningCharacter);
	DOREPLIFETIME(ASOGunBase, ClipSize);
	DOREPLIFETIME(ASOGunBase, MaxAmmoCapacity);
	DOREPLIFETIME(ASOGunBase, bInfiniteAmmo);
	DOREPLIFETIME(ASOGunBase, CurrentFireMode);
	DOREPLIFETIME(ASOGunBase, bIsEquipped);
	DOREPLIFETIME(ASOGunBase, bReloading);
	DOREPLIFETIME(ASOGunBase, bTrigger);
	DOREPLIFETIME(ASOGunBase, CurrentAmmo);
	DOREPLIFETIME(ASOGunBase, CurrentAmmoInClip);
}

void ASOGunBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		ASOCharacterBase* CharacterBase = Cast<ASOCharacterBase>(OtherActor);
		OwningCharacter = CharacterBase;
		if (OwningCharacter && !bIsEquipped)
		{
			bIsEquipped = true;
			OwningCharacter->EquipItem(this);
			CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void ASOGunBase::PressLMB()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
	OnFire(CurrentFireMode);
}

void ASOGunBase::ReleaseLMB()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
	StopFire();
}

EALSOverlayState ASOGunBase::GetOverlayState() const
{
	return WeaponData.OverlayState;
}

void ASOGunBase::OnFire(ESOFireMode InFireMode)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
	if (!bIsEquipped) return;
	if (bReloading || CurrentAmmoInClip <= 0) return;
	switch (InFireMode)
	{
	case ESOFireMode::Auto:
		FireAuto();
		break;
	case ESOFireMode::Burst:
		FireBurst(MaxRepeatCount);
		break;
	case ESOFireMode::Single:
		FireSingle();
		break;
	default:
		break;
	}
}

void ASOGunBase::FireAuto()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);

	FireProjectile();
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ASOGunBase::FireProjectile, FireInterval, true);
}

void ASOGunBase::FireBurst(uint32 InMaxRepeatCount)
{
	SO_LOG(LogSOTemp, Warning, TEXT("Begin"))
	const int InitialRepeatCount = 0;
	// 점사 횟수, 필요에 따라 변경

	FireContinuously(InitialRepeatCount, InMaxRepeatCount);
}

void ASOGunBase::FireContinuously(int32 InCurRepeatCount, int32 InMaxRepeatCount)
{
	// SO_LOG(LogSOTemp, Warning, TEXT("%d %d"), InCurRepeatCount, InMaxRepeatCount)
	if(InCurRepeatCount >= InMaxRepeatCount)
	{
		// SO_LOG(LogSOTemp, Warning, TEXT("%d"), InCurRepeatCount >= InMaxRepeatCount)
		GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle);
		return;
	}
	FireProjectile();
	
	GetWorld()->GetTimerManager().SetTimer(
		BurstTimerHandle,
		[this, InCurRepeatCount, InMaxRepeatCount]()
		{
			FireContinuously(InCurRepeatCount + 1, InMaxRepeatCount);
		},
		FireInterval, false);
}

void ASOGunBase::FireSingle()
{
	SO_LOG(LogSOTemp, Warning, TEXT("Begin"))
	FireProjectile();
}

void ASOGunBase::FireProjectile()
{
	SO_LOG(LogSOTemp, Warning, TEXT("Begin"))
	AController* OwnerController = OwningCharacter->GetController();
	if (OwnerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerController"));
		return;
	}

	// Viewport LineTrace
	FHitResult ScreenLaserHit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	// 화면 중앙 LineTrace
	FVector TraceStartLocation;
	FRotator TraceStartRotation;
	OwnerController->GetPlayerViewPoint(TraceStartLocation, TraceStartRotation);

	// DrawDebugCamera(GetWorld(), TraceStartLocation, TraceStartRotation, 90, 2, FColor::Red, true);
	
	FVector TraceEnd = TraceStartLocation + TraceStartRotation.Vector() * MaxRange;
	bool bScreenLaserSuccess = GetWorld()->LineTraceSingleByChannel(ScreenLaserHit, TraceStartLocation, TraceEnd, ECC_Projectile, Params);
	
	// 허공이면 TraceEnd, 아니면 Hit.Location
	FVector HitLocation = bScreenLaserSuccess ? ScreenLaserHit.Location : TraceEnd;
	// UE_LOG(LogTemp, Log, TEXT("ScreenLaserHit : %s "), *HitLocation.ToString());

	// 소켓 위치
	FTransform MuzzleSocketTransform;
	const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(MuzzleSocketName);
	// ensure(AmmoEjectSocket);
	if(IsValid(AmmoEjectSocket))
	{
		MuzzleSocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);		
	}

	DrawDebugLine(GetWorld(), MuzzleSocketTransform.GetLocation(), TraceEnd, FColor::Red,false, 5, 0, 2);
	DrawDebugPoint(GetWorld(), ScreenLaserHit.Location, 3, FColor::Red, false, 5,0);
	
	// 스폰 위치, 도착지점
	// MuzzleLocation, HitLocation
	ServerRPCOnFire(MuzzleSocketTransform, HitLocation);
}

void ASOGunBase::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	if (OwningCharacter == nullptr || OwningCharacter->GetController() == nullptr)
	{
		return;
	}

	/*APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerPawn"));
		return;
	}
	
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerController"));
	}*/
	
	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	
	// Try and fire a projectile
	if (ProjectileClass  == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("ProjectileClass is null"));
		return;
	}
	
	FVector SpawnLocation = MuzzleTransform.GetLocation(); 
	FVector ToTarget = HitLocation - SpawnLocation;	
	FRotator SpawnRotation = ToTarget.Rotation();
	
	// Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.Owner = GetOwner();
	ActorSpawnParams.Instigator = InstigatorPawn;
	//ASOProjectileBase* Projectile = nullptr;
	
	// 서버에서 생성하면 자동 리플리케이션
	//Projectile = GetWorld()->SpawnActor<ASOProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	//if(Projectile) Projectile->SetOwner(OwningCharacter);		
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))

	//검사 로직 추가 
	ASOProjectileBase* Bullet = ProjectilePoolComponent->PullProjectile();
	// 데미지 강화 Bullet->CurrentDamage = Bullet->BaseDamage + DamageIncrease;
	if(Bullet)
	{
		Bullet->SetActorLocation(SpawnLocation);
		Bullet->SetActorRotation(SpawnRotation);
		Bullet->ProjectileMesh->SetVisibility(true);
		Bullet->SetProjectileActive(true);
		Bullet->SetLifeSpanToPool();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Bullet"));
	}
}

void ASOGunBase::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ASOGunBase::ShowEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation)
{
}

void ASOGunBase::PlaySound()
{
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, OwningCharacter->GetActorLocation());
	}
}

void ASOGunBase::Recoil()
{
	
}

void ASOGunBase::Reload()
{
	
}

void ASOGunBase::Aim()
{
}

void ASOGunBase::Equip()
{	
	if (!bIsEquipped) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	const USkeletalMeshSocket* HandSocket = OwningCharacter->GetMesh()->GetSocketByName(AttachPoint);
	if (HandSocket)
	{
		HandSocket->AttachActor(this, OwningCharacter->GetMesh());
	}
	this->AttachToComponent(OwningCharacter->GetMesh(), AttachmentRules, AttachPoint);
	//	HeldObjectRoot->SetRelativeLocation(Offset);
}

void ASOGunBase::SetGunData(const uint8 InID)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is not available."));
		return;
	}

	// 게임 인스턴스 가져오기.
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is not available."));
		return;
	}

	// 게임 인스턴스에서 서브시스템을 가져오기.
	USOGameSubsystem* SOGameSubsystem = GameInstance->GetSubsystem<USOGameSubsystem>();
	if (!SOGameSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("SOGameSubsystem is not available."));
		return;
	}

	// 서브시스템에서 원하는 ID의 WeaponStatData를 가져오기.
	FSOWeaponStat* SelectedWeaponStat = SOGameSubsystem->GetWeaponStatData(InID);
	if (SelectedWeaponStat)
	{
		WeaponStat = *SelectedWeaponStat;
	}

	FSOWeaponData* SelectedWeaponData = SOGameSubsystem->GetWeaponData(InID);
	if (SelectedWeaponData)
	{
		WeaponData = *SelectedWeaponData;
		WeaponMesh->SetSkeletalMesh(WeaponData.SkeletalMesh);
		AttachPoint = WeaponData.SocketName;
		AmmoClass =  WeaponData.AmmoClass;
	}

	if(AmmoClass)
	{
		ProjectilePoolComponent->SetAmmoClass(AmmoClass);
	}
}

void ASOGunBase::DisablePhysics()
{
	UE_LOG(LogTemp, Log, TEXT("DisablePhysics"));
	WeaponMesh->SetSimulatePhysics(false);
}

void ASOGunBase::ServerRPCOnFire_Implementation(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	CreateProjectile(MuzzleTransform, HitLocation);
	MulticastRPCShowEffect(MuzzleTransform, HitLocation);	
}

void ASOGunBase::MulticastRPCShowEffect_Implementation(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	// FQuat을 FRotator로 변환
	FRotator MuzzleRotation = MuzzleTransform.GetRotation().Rotator();

	// ShowEffect 함수 호출 시 변환된 FRotator 사용
	ShowEffect(MuzzleTransform.GetLocation(), MuzzleRotation);
	PlaySound();
}



int32 ASOGunBase::CalculateAvailableFireModeCount()
{
	uint8 Mode = AvailableFireMode;
	int32 Count = 0;
	while (Mode)
	{
		Count += Mode & 1;
		Mode >>= 1;
	}
	return Count;
}

void ASOGunBase::InitCurrentFireMode()
{
	// 초기 사격 모드 초기화
	for(uint8 i = 1; i <= static_cast<uint8>(ESOFireMode::Max); i <<= 1)
	{
		// 작은 수부터 시작해서 낮은 비트 시 break;
		if(AvailableFireMode & i)
		{
			CurrentFireMode = static_cast<ESOFireMode>(i);
			break;		
		}
	}
}

ESOFireMode ASOGunBase::GetNextValidFireMode()
{
	// 순환 방식으로 다음 발사 모드를 반환
	uint8 CurrentMode = static_cast<uint8>(CurrentFireMode);
	uint8 NextMode = CurrentMode << 1;

	StopFire();

	// 가능한 모드인가?
	// true = 불가능한 모드 = 다음 모드 탐색
	// false = 가능 = 탈출 후 반환
	while ((NextMode & AvailableFireMode) == 0)
	{
		// 다음 모드
		NextMode <<= 1;
		// 만약 다음 모드가 끝에 도달 시 원복
		if (NextMode == static_cast<uint8>(ESOFireMode::Max))
		{
			// Auto로 복귀
			NextMode = 1;
		}
	}

	return static_cast<ESOFireMode>(NextMode);
}
