// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOGunBase.h"
#include "SOSniper.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API ASOSniper : public ASOGunBase
{
	GENERATED_BODY()

public:
	ASOSniper();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	/** IDamageable **/
public:
	virtual void PressLMB() override;

	/* Member Function */
public:
	virtual void Equip() override;
	
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

	
/*public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Lens;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USceneCaptureComponent2D> CaptureCamera;*/

	
};
