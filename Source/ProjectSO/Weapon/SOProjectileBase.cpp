// Fill out your copyright notice in the Description page of Project Settings.


#include "SOProjectileBase.h"

#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystemInstanceController.h"
#include "Components/AudioComponent.h"

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
		StartDestroyTimer();
	}	
}

// Called every frame
void ASOProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASOProjectileBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroyed();

	// 이하는 자식에서 구현
	APawn* FiringPawn = GetInstigator();
	if (FiringPawn && HasAuthority())
	{
		AController* FiringController = FiringPawn->GetController();
		if (FiringController)
		{
			UE_LOG(LogTemp, Warning, TEXT("OtherActor : %s"), *OtherActor->GetName());
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
		ProjectileMesh->SetVisibility(false);
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

