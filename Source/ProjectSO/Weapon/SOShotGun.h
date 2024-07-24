// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOGunBase.h"
#include "SOShotGun.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API ASOShotGun : public ASOGunBase
{
	GENERATED_BODY()

public:
	ASOShotGun();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	/** IDamageable **/
public:
	virtual void PressLMB() override;
	
	// Fire Logic
protected:
	virtual void OnFire() override;
	virtual void AutoFire() override;
	virtual void BurstFire() override;
	virtual void SingleFire() override;
	virtual void FireProjectile() override;
	virtual void CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation) override;

	// Effect
protected:
	virtual void ShowEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation) override;
	virtual void PlaySound() override;
	virtual void Recoil() override;

protected:
	virtual void Reload() override;
	virtual void Aim() override;
	
};
