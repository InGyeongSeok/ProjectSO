// Fill out your copyright notice in the Description page of Project Settings.


#include "SOProjectileBase.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystemInstanceController.h"
#include "Components/AudioComponent.h"
#include "Net/UnrealNetwork.h"
#include "Projectile/SOProjectilePoolComponent.h"
#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Character/SOCharacterBase.h"
#include "ProjectSO/Core/SOGameSubsystem.h"
#include "ProjectSO/Library/SOProjectileHitEffectDataAsset.h"

// Sets default values
ASOProjectileBase::ASOProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	// SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// SetRootComponent(SceneComponent);
	
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->SetIsReplicated(true);
	// CollisionComp->SetupAttachment(SceneComponent);
	SetRootComponent(CollisionComp);
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	ProjectileMesh->SetupAttachment(CollisionComp);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMesh->SetVisibility(false);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	

	LifeSpanTime = 3.0f;
	HideStartTime = 0.0f;
	ShowStartTime = 0.0f;
	
	// NeullCullDistance 
	// NetCullDistanceSquared = FLT_MAX; 
}

// Called when the game starts or when spawned
void ASOProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	// SetProjectileSurfaceEffectData();
	if (Tracer)
	{
		TracerComponent = UGameplayStatics::SpawnEmitterAttached
		(
			Tracer,
			CollisionComp,
			FName(),
			GetActorLocation(),
			GetActorRotation(),
			EAttachLocation::KeepWorldPosition
		);
	}
	
	// CollisionComp->OnComponentHit.AddDynamic(this, &ACHProjectile::OnHit);
	if (HasAuthority())
	{
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASOProjectileBase::OnBeginOverlap);
		// StartDestroyTimer();
	}
}

// Called every frame
void ASOProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// SO_LOG(LogSOProjectileBase, Warning, TEXT("%s"), *ProjectileMovementComponent->Velocity.ToString())

}

void ASOProjectileBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASOProjectileBase, HideStartTime);
	DOREPLIFETIME(ASOProjectileBase, ShowStartTime);
}

void ASOProjectileBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 사람에 맞았을때로 설정하기
	if (ProjectileData.FiringPawn && HasAuthority() && Cast<APawn>(OtherActor))
	{
		// ASOGunBase* GunBase = Cast<ASOGunBase>(Owner);
		
		FRuntimeFloatCurve DistanceDamageFalloff = ProjectileData.DistanceDamageFalloff;
	
		FVector HitLocation = SweepResult.ImpactPoint; 
		float Dist = FVector::Dist(ProjectileData.Location, HitLocation);  
		const FRichCurve* Curve = DistanceDamageFalloff.GetRichCurveConst();	
		SO_LOG(LogSOProjectileBase, Warning, TEXT("Dist : %f"), Dist)
	
		// 거리에 데미지 영향주는 변수
		float RangeModifier = 1.0f;
		check(Curve);
		if(Curve)
		{
			RangeModifier = Curve->HasAnyData() ? Curve->Eval(Dist) : 1.0f;
			RangeModifier *= PERCENT;
			SO_LOG(LogSOProjectileBase, Warning, TEXT("RangeModifier : %f"), RangeModifier)
		}
		else
		{
			SO_LOG(LogSOProjectileBase, Error, TEXT("Curve is null"))
		}

		
		AController* FiringController = ProjectileData.FiringPawn->GetController();
		if (FiringController)
		{
			AActor* HitActor = OtherActor;
			float Damage = 0.f;
			
			// SO_LOG(LogSOProjectileBase, Warning, TEXT("SweepResult.BoneName.ToString(): %s"), *SweepResult.BoneName.ToString())
			// SO_LOG(LogSOProjectileBase, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName())
			// SO_LOG(LogSOProjectileBase, Warning, TEXT("GetKeyByName: %s"), *GetKeyByBonName( SweepResult.BoneName.ToString()))

			//FString test = "Head";
			
			// Damage = Base damage × Hit area damage × Weapon class area damage
			// PERCENT 매크로 사용하자
			// Base Damage
			float BaseDamage = ProjectileData.Damage;
			SO_LOG(LogSOProjectileBase, Warning, TEXT("BaseDamage : %f"), BaseDamage)
			
			// subsystem 가지고 오기
			USOGameSubsystem* SOGameSubsystem = GetSOGameSubsystem();
		
			// Hit area damage
			FString StringBoneName = SweepResult.BoneName.ToString();
			FString HitBoneArea = GetKeyByBonName(*StringBoneName);

			float HitAreaDamage = SOGameSubsystem->GetHitAreaDamage(HitBoneArea);

			if(HitAreaDamage<0) // -1이 리턴된 경우? 
			{
				UE_LOG(LogTemp,Log,TEXT(" Bone Name  1  ::: %s"), *HitBoneArea );

				ASOCharacterBase* CharacterBase = Cast<ASOCharacterBase>(OtherActor);
				if(CharacterBase)
				{
					StringBoneName = CharacterBase->GetHitParentBone(SweepResult.BoneName);
					UE_LOG(LogTemp,Log,TEXT(" Bone Name  2  ::: %s"), *StringBoneName );

					HitBoneArea =  GetKeyByBonName(*StringBoneName);
				}
			}
			
			SO_LOG(LogSOProjectileBase, Warning, TEXT("Hitareadamage : %f"), HitAreaDamage * PERCENT)
			
			ESOWeaponType WeaponTypeEnum = ProjectileData.WeaponType;
			FString WeaponTypeString = UEnum::GetValueAsString(ProjectileData.WeaponType);
			float WeaponClassAreaDamage = SOGameSubsystem->GetWeaponClassAreaDamage(WeaponTypeString, HitBoneArea) * PERCENT;
			SO_LOG(LogSOProjectileBase, Warning, TEXT("WeaponType : %s"), *WeaponTypeString)
			SO_LOG(LogSOProjectileBase, Warning, TEXT("Weaponclassareadamage : %f"), WeaponClassAreaDamage)
			
			
			Damage = BaseDamage * HitAreaDamage * WeaponClassAreaDamage * RangeModifier;
			SO_LOG(LogSOProjectileBase, Warning, TEXT("Damage : %f"), Damage)
			
			UGameplayStatics::ApplyDamage(HitActor,Damage,FiringController,this,UDamageType::StaticClass());
		}
	}
	else
	{
		AActor* HitActor =  SweepResult.GetActor();
		const FVector HitLocation = SweepResult.Location;
		const FVector HitNormal = SweepResult.Normal;
		MulticastRPCPlayHitEffectBySurface(HitActor, HitLocation, HitNormal);
		// PlayHitEffectBySurface(HitActor, HitLocation, HitNormal);		
	}
	
	if (ImpactParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, GetActorTransform());
	}
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}
	if (ProjectileMesh)
	{
		// 클라이언트에게 숨기라고 지시 OnRep_HideStartTime
		HideStartTime = GetWorld()->GetTimeSeconds();
	}
	if (CollisionComp)
	{
		SetProjectileActive(false);
	}
	if (TrailSystemComponent && TrailSystemComponent->GetSystemInstanceController())
	{
		TrailSystemComponent->GetSystemInstanceController()->Deactivate();
	}
	if (ProjectileLoopComponent && ProjectileLoopComponent->IsPlaying())
	{
		ProjectileLoopComponent->Stop();
	}
	// 충돌하면 Pool로 들어가게 설정
}

//
void ASOProjectileBase::Destroyed()
{
	Super::Destroyed();
	if (ImpactParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, GetActorTransform());
	}
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}
}

void ASOProjectileBase::StartDestroyTimer()
{
	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(
		DestroyTimer,
		this,
		&ASOProjectileBase::DestroyTimerFinished,
		DestroyTime
	);
}
void ASOProjectileBase::DestroyTimerFinished()
{
	Destroy();
}
void ASOProjectileBase::SetProjectileActive(bool IsActive)
{
	// 액터 전체 충돌 관리
	SetActorEnableCollision(IsActive); 
	SetActorTickEnabled(IsActive);
	if (!IsActive)
	{
		HideStartTime = GetWorld()->GetTimeSeconds();
		ProjectileMovementComponent->bSimulationEnabled = false;
		ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	}
	else
	{
		ShowStartTime = GetWorld()->GetTimeSeconds();
		ProjectileMovementComponent->bSimulationEnabled = true;
		ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
		ProjectileMovementComponent->Velocity = GetActorForwardVector() * 7000.0f;
	}
}

void ASOProjectileBase::SetLifeSpanToPool()
{
	FTimerHandle TimerHandle_LifeSpanToPoolExpired;
	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(TimerHandle_LifeSpanToPoolExpired, this, &ASOProjectileBase::PushPoolSelf, LifeSpanTime);
	}
}

void ASOProjectileBase::PushPoolSelf()
{
	if (ProjectilePool == nullptr)
	{
		return;
	}
	ProjectilePool->ReturnToPool(this);
	SetActorLocation(SpawnTransform.GetLocation());
	SetActorRotation(SpawnTransform.Rotator());
	ProjectileMovementComponent->StopMovementImmediately();
}

// Server에서 호출
void ASOProjectileBase::InitializeProjectile(const FProjectileData& InData)
{
	ProjectileData = InData;
	//SpawnLocation = InData.Location;
	SO_LOG(LogSOProjectileBase, Warning, TEXT("Owner : %s"), Owner == nullptr ? TEXT("Null") :  *Owner->GetName());
	SO_LOG(LogSOProjectileBase, Warning, TEXT("Owner : %s"), Owner == nullptr ? TEXT("Null") :  *Owner->GetName());
	SetActorLocationAndRotation(ProjectileData.Location, ProjectileData.Rotation);
	SetProjectileActive(true);
	//FiringPawn = InData.FiringPawn;
	SetLifeSpanToPool();
}

FString ASOProjectileBase::GetKeyByBonName(const FString& InBoneName)
{
	int32 UnderscoreIndex;
	if (InBoneName.FindChar(TEXT('_'), UnderscoreIndex))
	{
		return InBoneName.Left(UnderscoreIndex);
	}
	return InBoneName;
}

USOGameSubsystem* ASOProjectileBase::GetSOGameSubsystem()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is not available."))
		return nullptr;
	}

	// 게임 인스턴스 가져오기.
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is not available."))
		return nullptr;
	}

	// 게임 인스턴스에서 서브시스템을 가져오기.
	USOGameSubsystem* SOGameSubsystem = GameInstance->GetSubsystem<USOGameSubsystem>();
	if (!SOGameSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("SOGameSubsystem is not available."))
		return nullptr;
	}
	return SOGameSubsystem;
}

void ASOProjectileBase::PlayHitEffectBySurface(AActor* HitActor, const FVector& HitLocation, const FVector& HitNormal)
{	
	const TArray<FName>& ActorTags = HitActor->Tags;
	// 태그를 서브 시스템
	// 나이아가라를 받아오기
	// SubSystem::Nia* GetNia(FName Tag)
	USOGameSubsystem* SOGameSubsystem = GetSOGameSubsystem();
	UNiagaraSystem* SelectedEffect = SOGameSubsystem->GetSurfaceEffect(ActorTags);
	if(SelectedEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SelectedEffect, HitLocation, HitNormal.Rotation());		
	}
	
	SO_LOG(LogSOProjectileBase, Log, TEXT("HitActor : %s"), *HitActor->GetName())
	
	/*for (const FName& Tag : ActorTags)
	{
		SO_LOG(LogSOProjectileBase, Log, TEXT("Tag : %s"), *Tag.ToString())
		if (ProjectileHitEffectDataAsset->EffectBySurface.Contains(Tag))
		{
			UNiagaraSystem* SelectedEffect = ProjectileHitEffectDataAsset->EffectBySurface[Tag];
			if(SelectedEffect)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SelectedEffect, HitLocation, HitNormal.Rotation());					
				SO_LOG(LogSOProjectileBase, Log, TEXT("SelectedEffect : %s"), *SelectedEffect->GetName())
			}
			else
			{
				SO_LOG(LogSOProjectileBase, Log, TEXT("SelectedEffect is Null"))
			}
		}		
		break;
	}	*/
}

void ASOProjectileBase::SetProjectileSurfaceEffectData()
{
	SO_LOG(LogSOTemp,Log,TEXT("Begin"))

	// 게임 인스턴스에서 서브시스템을 가져오기.
	// USOGameSubsystem* SOGameSubsystem = GetSOGameSubsystem();	

	// ProjectileHitEffectDataAsset = SOGameSubsystem->GetProjectileHitEffectDataAsset();
	// EffectBySurface = ProjectileHitEffectDataAsset
	
}

void ASOProjectileBase::MulticastRPCPlayHitEffectBySurface_Implementation(AActor* HitActor, const FVector& HitLocation, const FVector& HitNormal)
{
	// Owner가 없어서 동기화가 안됨.
	PlayHitEffectBySurface(HitActor, HitLocation, HitNormal);
}

// 메시 숨기기
void ASOProjectileBase::OnRep_HideStartTime() 
{
	ProjectileMesh->SetVisibility(false);
}

FRichCurve* ASOProjectileBase::GetCurveData()
{
	// DistanceDamageFalloff.GetRichCurveConst();
	//Todo @김윤수 커브 데이터 반환해주세요 
	return nullptr;
}

// 메시 보이게 하기
void ASOProjectileBase::OnRep_ShowStartTime()
{
	
	ProjectileMesh->SetVisibility(true);
}


