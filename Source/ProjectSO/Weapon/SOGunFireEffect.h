// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SOGunFireEffect.generated.h"

class UNiagaraSystem;
class UParticleSystem;

UCLASS()
class PROJECTSO_API ASOGunFireEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASOGunFireEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UFUNCTION()
	void PlayEffect(const FTransform& MuzzleTransform, const FTransform& EjectTransform);
	UFUNCTION()
	void PlayMuzzleEffect(const FTransform& MuzzleTransform);
	UFUNCTION()
	void PlayEjectAmmoEffect(const FTransform& EjectTransform);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties|Effect")
	TObjectPtr<class USkeletalMeshComponent> SkeletalMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Properties|Effect")
	TObjectPtr<class UParticleSystem> MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Properties|Effect")
	TObjectPtr<class UNiagaraSystem> EjectShellParticles;

};
