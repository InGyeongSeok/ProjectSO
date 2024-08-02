// Fill out your copyright notice in the Description page of Project Settings.


#include "SOProjectileBase.h"
#include "NiagaraComponent.h"
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

// Sets default values
ASOProjectileBase::ASOProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);
	
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->SetupAttachment(SceneComponent);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	ProjectileMesh->SetupAttachment(SceneComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	
	//Todo 숫자
	LifeSpanTime = 3.0f;
	bOnHitProjectile = false;
	bShowProjectile = false;
	InitialSpeed = 1000;
}

// Called when the game starts or when spawned
void ASOProjectileBase::BeginPlay()
{
	Super::BeginPlay();
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
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASOProjectileBase::OnHit);
		//StartDestroyTimer();
	}
	ProjectileMovementComponent->SetIsReplicated(true);
	AActor::SetReplicateMovement(true);
}

// Called every frame
void ASOProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASOProjectileBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASOProjectileBase, bOnHitProjectile);
	DOREPLIFETIME(ASOProjectileBase, bShowProjectile);
}

void ASOProjectileBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SO_LOG(LogTemp, Warning, TEXT("OtherActor : %s"), *OtherActor->GetName())
	//Destroyed();
	APawn* FiringPawn = GetInstigator();
	if (FiringPawn && HasAuthority())
	{
		SO_LOG(LogTemp, Warning, TEXT("1"))
		AController* FiringController = FiringPawn->GetController();
		if (FiringController)
		{
			SO_LOG(LogTemp, Warning, TEXT("2"))
			// const float DamageToCause = MuzzleLaserHit.BoneName.ToString() == FString("Head") ? HeadShotDamage : Damage;
			const float DamageToCause = Damage;
			AActor* HitActor = OtherActor;
			AController* OwnerController = FiringPawn->GetController();
	
			UGameplayStatics::ApplyDamage(HitActor,DamageToCause,OwnerController,this,UDamageType::StaticClass());
			UE_LOG(LogTemp, Log, TEXT("HitActor : %s"), *GetNameSafe(HitActor))
		}
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
		bOnHitProjectile = !bOnHitProjectile;
	}
	if (CollisionComp)
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (TrailSystemComponent && TrailSystemComponent->GetSystemInstanceController())
	{
		TrailSystemComponent->GetSystemInstanceController()->Deactivate();
	}
	if (ProjectileLoopComponent && ProjectileLoopComponent->IsPlaying())
	{
		ProjectileLoopComponent->Stop();
	}
}

//삭제하지 않고 오브젝트 풀에 들어간다. (이 함수 사용 X)
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

// 사용 X
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
	// SetActorHiddenInGame(!IsActive);
	SetActorEnableCollision(IsActive);
	SetActorTickEnabled(IsActive);
	
	if (!IsActive)
	{
		// ProjectileMovementComponent->Velocity = FVector::ZeroVector;
		ProjectileMovementComponent->StopMovementImmediately();
	}
	else
	{
		ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
		// ProjectileMovementComponent->Velocity = GetActorForwardVector() * 7000.0f;
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
	ProjectilePool->PushProjectileInPool(this);
	SetActorLocation(SpawnTransform.GetLocation());
	SetActorRotation(SpawnTransform.Rotator());
	
	// SetProjectileActive(false);

	ProjectileMovementComponent->StopMovementImmediately();
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	
	SO_LOG(LogTemp, Warning, TEXT("Pool Self : %d"), ProjectilePool->Pool.Num());
}

//Server에서 호출
void ASOProjectileBase::InitializeProjectile(FVector InLocation, FRotator InRotation)
{
	SO_LOG(LogSONetwork,Log,TEXT("LogSONetwork"));
	SetActorLocation(InLocation);
	SetActorRotation(InRotation);
	// SetProjectileActive(true);

	ProjectileMovementComponent->Velocity = GetActorForwardVector() * InitialSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = 1;

	// 3초 후에 Pool에 돌아오게 하는 로직
	// 이 함수에서 다시 중력과 속도를 초기화
	SetLifeSpanToPool();
	
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	bShowProjectile = !bShowProjectile;
}

//충돌했을 때 
void ASOProjectileBase::OnRep_OnHitProjectile() 
{
	SO_LOG(LogTemp, Warning, TEXT("Begin"))
	// ProjectileMesh->SetVisibility(false);
	// ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	ProjectileMovementComponent->StopMovementImmediately();
}

//총 발사할 때
void ASOProjectileBase::OnRep_ShowProjectile()
{
	SO_LOG(LogTemp, Warning, TEXT("Begin"))
	// ProjectileMesh->SetVisibility(true);
	// ProjectileMovementComponent->Velocity = GetActorForwardVector() * 7000.0f;
}

