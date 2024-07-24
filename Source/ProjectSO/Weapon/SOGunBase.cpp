// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGunBase.h"

#include "SOProjectileBase.h"
#include "Components/CapsuleComponent.h"
#include "KisMet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "ProjectSO/Character/SOCharacterBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectSO/Core/SOGameSubsystem.h"

// Sets default values
ASOGunBase::ASOGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	CollisionComp->InitCapsuleSize(40.0f, 50.0f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetVisibility(true, false);	
	WeaponMesh->SetupAttachment(CollisionComp);
	
	CurrentFireMode = ESOFireMode::Single;
	CurrentAmmoInClip = 30;

	
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
	FSOWeaponStat* SelectedWeaponStat  = SOGameSubsystem->GetWeaponStatData(InID);
	if(SelectedWeaponStat)
	{
		WeaponStat = *SelectedWeaponStat;
	}

	FSOWeaponData* SelectedWeaponData  = SOGameSubsystem->GetWeaponData(InID);
	if(SelectedWeaponData)
	{
		WeaponData = *SelectedWeaponData;
		WeaponMesh ->SetSkeletalMesh(WeaponData.SkeletalMesh);
		AttachPoint  =  WeaponData.SocketName;
	}
}


// Called when the game starts or when spawned
void ASOGunBase::BeginPlay()
{
	Super::BeginPlay();
	SetGunData(WeaponID);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASOGunBase::OnSphereBeginOverlap);
}

// Called every frame
void ASOGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASOGunBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(HasAuthority())
	{
		ASOCharacterBase* CharacterBase = Cast<ASOCharacterBase>(OtherActor);
		OwningCharacter = CharacterBase;
		if(OwningCharacter)
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
	OnFire();
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

void ASOGunBase::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
	if(!bIsEquipped) return;
	if(bReloading || CurrentAmmoInClip <= 0) return;
	switch (CurrentFireMode)
	{
	case ESOFireMode::Auto:
		AutoFire();
		break;
	case ESOFireMode::Burst:
		BurstFire();
		break;
	case ESOFireMode::Single:
		SingleFire();
		break;
	default:
		break;
	}
}

void ASOGunBase::AutoFire()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ASOGunBase::FireProjectile, FireInterval, true);
}

void ASOGunBase::BurstFire()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
	// 기존 타이머 정리
	GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle1);
	GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle2);

	FireProjectile();
	GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle1, this, &ASOGunBase::FireProjectile, FireInterval, false);
	GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle2, this, &ASOGunBase::FireProjectile, FireInterval * 2.0f, false);
}

void ASOGunBase::SingleFire()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
	FireProjectile();
}

void ASOGunBase::FireProjectile()
{
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
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
	bool bScreenLaserSuccess = GetWorld()->LineTraceSingleByChannel(ScreenLaserHit, TraceStartLocation, TraceEnd, ECollisionChannel::ECC_GameTraceChannel3, Params);


	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
	
	// 허공이면 TraceEnd, 아니면 Hit.Location
	FVector HitLocation = bScreenLaserSuccess ? ScreenLaserHit.Location : TraceEnd;
	UE_LOG(LogTemp, Log, TEXT("HitLocation : %s "), *HitLocation.ToString());

	// 소켓 위치
	FTransform MuzzleSocketTransform;
	const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(MuzzleSocketName);
	MuzzleSocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);

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
	ASOProjectileBase* Projectile = nullptr;
	
	// 서버에서 생성하면 자동 리플리
	Projectile = GetWorld()->SpawnActor<ASOProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	if(Projectile) Projectile->SetOwner(OwningCharacter);		
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__))
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
	if(!bIsEquipped) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	const USkeletalMeshSocket* HandSocket = OwningCharacter->GetMesh()->GetSocketByName(AttachPoint);
	if(HandSocket)
	{
		HandSocket->AttachActor(this,OwningCharacter->GetMesh());		
	}
	WeaponMesh->AttachToComponent(OwningCharacter->GetMesh(), AttachmentRules, AttachPoint);
	//	HeldObjectRoot->SetRelativeLocation(Offset);
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