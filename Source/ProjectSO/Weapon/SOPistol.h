// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOGunBase.h"
#include "SOPistol.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API ASOPistol : public ASOGunBase
{
	GENERATED_BODY()

public:
	ASOPistol();
	
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
	virtual void OnFire(ESOFireMode InFireMode) override;
	virtual void FireAuto() override;
	virtual void FireBurst(uint32 InMaxRepeatCount) override;
	virtual void FireSingle() override;
	virtual void FireProjectile() override;
	virtual void CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation) override;

	// Effect
protected:
	virtual void PlayMuzzleEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation) override;
	virtual void PlaySound() override;
	virtual void Recoil() override;

protected:
	virtual void Reload() override;
	virtual void Aim(bool bPressed) override;
};
