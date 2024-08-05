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
	virtual void OnFire(ESOFireMode InFireMode) override;
	virtual void FireAuto() override;
	virtual void FireBurst(uint32 InMaxRepeatCount) override;
	virtual void FireSingle() override;
	virtual void FireProjectile() override;
	virtual void CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation) override;

	FVector SpreadTraceEnd();

	// Effect
protected:
	virtual void PlayMuzzleEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation) override;
	virtual void PlaySound() override;
	virtual void Recoil() override;

protected:
	virtual void Reload() override;
	virtual void Aim() override;
	
	// Multi
protected:	
	UFUNCTION(Server, Unreliable)
	void ServerRPCOnFireShotGun(const FTransform& MuzzleTransform, const TArray<FVector>& InTraceEndArray);

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 Spread;

	UPROPERTY(EditDefaultsOnly)
	int32 ShrapnelCount;

};
