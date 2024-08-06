// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOGunFireEffect.h"
#include "GameFramework/Actor.h"
#include "Library/ALSCharacterEnumLibrary.h"
#include "ProjectSO/Library/SOWeaponEnumLibrary.h"
#include "ProjectSO/Library/SOWeaponStructLibrary.h"
#include "ProjectSO/Interface/SODamageableInterface.h"
#include "ProjectSO/Interface/SOEquippableInterface.h"
#include "SOGunBase.generated.h"

class ASOCharacterBase;
class USkeletalMeshComponent;

UCLASS()
class PROJECTSO_API ASOGunBase : public AActor, public ISODamageableInterface, public ISOEquippableInterface
{
	GENERATED_BODY()
	
public:	
	ASOGunBase();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** IDamageable **/
public:
	virtual void PressLMB() override;
	virtual void ReleaseLMB() override;

	/** IEquippableInterface **/
public:
	virtual EALSOverlayState GetOverlayState() const override;

	/* Member Function */
public:
	virtual void Equip();
	virtual void SetOwningCharacter(ASOCharacterBase* InOwningCharacter);
	
	// Fire Logic
protected:
	virtual void OnFire(ESOFireMode InFireMode);
	virtual void FireAuto();
	virtual void FireBurst(uint32 InMaxRepeatCount);
	virtual void FireContinuously(int32 InCurRepeatCount, int32 InMaxRepeatCount);
	virtual void FireSingle();
	virtual void FireProjectile();
	virtual void CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation);
	virtual void StopFire();

	// Effect
protected:
	virtual void PlayMuzzleEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation);
	virtual void PlayEjectAmmoEffect(const FVector& EjectLocation, FRotator& EjectRotation);
	virtual void PlaySound();
	virtual void Recoil();

public:
	virtual void Reload();
	virtual void Aim(bool bPressed);

public:
	uint8 GetScopeAim() { return bScopeAim; }
	
	// Data Settings
protected:
	virtual void SetGunData(const uint8 InID);

	// simulatePhysics
protected:
	void DisablePhysics();

	// Multi
protected:	
	UFUNCTION(Server, Unreliable)
	void ServerRPCOnFire(const FTransform& MuzzleTransform, const FVector& HitLocation);

	UFUNCTION()
	void OnRep_FireStartTime();
public:
	uint8 GetAvailableFireMode() const {return WeaponStat.FireMode;}
	int32 GetAvailableFireModeCount() const {return AvailableFireModeCount;}
	int32 CalculateAvailableFireModeCount();
	
	void InitCurrentFireMode();
	
	ESOFireMode GetCurrentFireMode() const { return CurrentFireMode; }
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentFireMode(ESOFireMode NewCurrentFireMode) { CurrentFireMode = NewCurrentFireMode; }
	
	ESOFireMode GetNextValidFireMode();

	FTransform GetSocketTransformByName( FName InSocketName, const class USkeletalMeshComponent* SkelComp);
	// Owner
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	TObjectPtr<class ASOCharacterBase> OwningCharacter;


	/** Projectile class to spawn */
	// UPROPERTY(EditAnywhere, Category = "Properties")
	// TSubclassOf<class ASOProjectileBase> ProjectileClass;

	/** Projectile class to spawn */
	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<class ASOGunFireEffect> FireEffectActor;
	
	// Component
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCapsuleComponent> CollisionComp;

	// Properties
protected:
	//여기 구조체 생각  
	UPROPERTY(EditAnywhere, Category = "Properties|Fire")
	int32 MaxRepeatCount;

	UPROPERTY(EditAnywhere, Category = "Properties|Weapon")
	FName AmmoEjectSocketName;

	// Ammo 구조체 생각해보기 
protected:
	// maximum bullet capacity
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Properties|Ammo")
	int32 MaxAmmoCapacity;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Properties|Ammo")
	uint8 bInfiniteAmmo : 1;

	// State
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated,Category = "Properties|State")
	ESOFireMode CurrentFireMode;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated, Category = "Properties|State")
	uint8 bIsEquipped : 1;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated, Category = "Properties|State")
	uint8 bReloading : 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated,Category = "Properties|State")
	uint8 bTrigger : 1;
	
	// Ammo player have except in clip
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "Properties|State")
	int32 CurrentAmmo;

	// How much ammo in the clip
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "Properties|State")
	int32 CurrentAmmoInClip;

	FTimerHandle FireTimerHandle;
	FTimerHandle BurstTimerHandle;
	
	// Struct Stat & Data
protected:

	UPROPERTY(EditInstanceOnly)
	int32 ID;
	
	
	UPROPERTY(VisibleAnywhere)
	FSOWeaponStat WeaponStat;

	UPROPERTY(VisibleAnywhere)
	FSOWeaponData WeaponData;
	
	// Ammo
protected:
	UPROPERTY()
	TObjectPtr<class USOProjectilePoolComponent> ProjectilePoolComponent; 
	
	//TSubclassOf<ASOProjectileBase> AmmoClass;

protected:
	int32 AvailableFireModeCount;

	UPROPERTY(ReplicatedUsing = OnRep_FireStartTime)
	float FireStartTime;

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float HoldThreshold;
	
	float PressedTime;
	float ReleasedTime;
	uint8 bScopeAim : 1;
};
