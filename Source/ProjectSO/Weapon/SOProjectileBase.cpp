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
	HideStartTime = GetWorld()->GetTimeSeconds();
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
	SO_LOG(LogSOProjectileBase, Warning, TEXT("OtherActor : %s"), *OtherActor->GetName())

	// Destroyed();	
	// 충돌한 액터가 프로젝타일 경우
	// ASOProjectileBase* OtherProjectile = Cast<ASOProjectileBase>(OtherActor);
	// if (OtherProjectile)
	// {
	// 	  return;
	// }
	
	FVector HitLocation = SweepResult.ImpactPoint; 
	float Dist = FVector::Dist(SpawnLocation, HitLocation);
	const FRichCurve* Curve = GetCurveData(); 

	// 거리에 데미지 영향주는 변수
	float RangeModifier = 1.0f;
	check(Curve);
	if(Curve)
	{
		RangeModifier = Curve->HasAnyData() ? Curve->Eval(Dist) : 1.0f;		
	}
	else
	{
		SO_LOG(LogSOProjectileBase, Error, TEXT("Curve is null"))
	}
	
	
	// APawn* FiringPawn = GetInstigator();
	if (FiringPawn && HasAuthority())
	{
		AController* FiringController = FiringPawn->GetController();
		if (FiringController)
		{
			const float DamageToCause = SweepResult.BoneName.ToString() == FString("Head") ? HeadShotDamage : Damage;
			AActor* HitActor = OtherActor;
			SO_LOG(LogSOProjectileBase, Warning, TEXT("SweepResult.BoneName.ToString(): %s"), *SweepResult.BoneName.ToString())
			SO_LOG(LogSOProjectileBase, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName())
			UGameplayStatics::ApplyDamage(HitActor,DamageToCause,FiringController,this,UDamageType::StaticClass());
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
		ProjectileMovementComponent->bSimulationEnabled = false;
		ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	}
	else
	{
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
	ProjectilePool->PushProjectileInPool(this);
	SetActorLocation(SpawnTransform.GetLocation());
	SetActorRotation(SpawnTransform.Rotator());
	
	// SetProjectileActive(false);

	ProjectileMovementComponent->StopMovementImmediately();
	// ProjectileMovementComponent->ProjectileGravityScale = 0;
	
}

// Server에서 호출
void ASOProjectileBase::InitializeProjectile(FVector InLocation, FRotator InRotation, APawn* InFiringPawn)
{
	SpawnLocation = InLocation;
	SetActorLocation(InLocation);
	SetActorRotation(InRotation);
	SetProjectileActive(true);

	// 
	FiringPawn = InFiringPawn;
	// ProjectileMovementComponent->Velocity = GetActorForwardVector() * InitialSpeed;
	// ProjectileMovementComponent->ProjectileGravityScale = 1;

	// 3초 후에 Pool에 돌아오게 하는 로직
	// 이 함수에서 다시 중력과 속도를 초기화
	SetLifeSpanToPool();
	// 클라이언트에게 보이게 하라고 지시 OnRep_ShowStartTime
	ShowStartTime = GetWorld()->GetTimeSeconds();
}

// 충돌했을 때 
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

//총 발사할 때
void ASOProjectileBase::OnRep_ShowStartTime()
{
	
	ProjectileMesh->SetVisibility(true);
}


