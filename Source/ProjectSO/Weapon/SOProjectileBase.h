// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SOProjectileBase.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class PROJECTSO_API ASOProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASOProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UBoxComponent* GetCollisionComp() const { return CollisionComp; }
	
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovementComponent; }

protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	

	virtual void Destroyed() override;
	
	void StartDestroyTimer();
	void DestroyTimerFinished();

	// ProjectilePool 
public:	
	UFUNCTION()
	void SetProjectileActive(bool IsActive);
	
	UFUNCTION()
	void SetLifeSpanToPool();

	UFUNCTION()
	void PushPoolSelf();

	UFUNCTION()
	void InitializeProjectile(FVector InLocation, FRotator InRotation, APawn* InFiringPawn);
	
	 
protected:
	
	
	
protected:
	// Multi
	UFUNCTION()
	void OnRep_ShowStartTime();

	UFUNCTION()
	void OnRep_HideStartTime();

	// Component
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> CollisionComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY()
	TObjectPtr<class UNiagaraComponent> TrailSystemComponent;

	UPROPERTY()
	TObjectPtr<class UParticleSystemComponent> TracerComponent;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystem> ImpactParticles;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundCue> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraSystem> TrailSystem;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> Tracer;	

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundCue> ProjectileLoop;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> ProjectileLoopComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundAttenuation> LoopingSoundAttenuation;
	
protected:
	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	UPROPERTY(EditAnywhere)
	float HeadShotDamage = 40.f;
	
	UPROPERTY(EditAnywhere)
	float DestroyTime = 4.f;

	UPROPERTY(EditDefaultsOnly)
	float InitialSpeed;

	UPROPERTY(EditDefaultsOnly)
	FTransform SpawnTransform;

	UPROPERTY()
	TObjectPtr<APawn> FiringPawn;
	
public:
	//pool
	UPROPERTY()
	TObjectPtr<class USOProjectilePoolComponent> ProjectilePool;
	
	UPROPERTY()
	float LifeSpanTime;
	
	UPROPERTY(ReplicatedUsing = OnRep_HideStartTime)
	float HideStartTime;
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_ShowStartTime)
	float ShowStartTime;

public:
	FRichCurve* GetCurveData();
private:
	FVector SpawnLocation;	
};
