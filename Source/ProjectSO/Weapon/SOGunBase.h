// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Library/ALSCharacterEnumLibrary.h"

#include "ProjectSO/Library/SOWeaponEnumLibrary.h"
#include "ProjectSO/Library/SOWeaponStructLibrary.h"
#include "ProjectSO/Interface/SODamageableInterface.h"
#include "ProjectSO/Interface/SOEquippableInterface.h"
#include "SOGunBase.generated.h"

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
	
	// Fire Logic
protected:
	virtual void OnFire(ESOFireMode InFireMode);
	virtual void FireAuto();
	virtual void FireBurst();
	virtual void FireSingle();
	virtual void FireProjectile();
	virtual void CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation);
	virtual void StopFire();

	// Effect
protected:
	virtual void ShowEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation);
	virtual void PlaySound();
	virtual void Recoil();

	virtual void Reload();
	virtual void Aim();

	// Data Settings
protected:
	void SetGunData(const uint8 InID);

	// simulatePhysics
protected:
	void DisablePhysics();

	// Multi
protected:	
	UFUNCTION(Server, Unreliable)
	void ServerRPCOnFire(const FTransform& MuzzleTransform, const FVector& HitLocation);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCShowEffect(const FTransform& MuzzleTransform, const FVector& HitLocation);

	// Owner
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	TObjectPtr<class ASOCharacterBase> OwningCharacter;

	/** Projectile class to spawn */
	UPROPERTY(EditAnywhere, Category = "CHGunBase|Properties")
	TSubclassOf<class ASOProjectileBase> ProjectileClass;
	
	// Component
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCapsuleComponent> CollisionComp;
	
	// Montage
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<class UAnimMontage> EquipMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<class UAnimMontage> FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<class UAnimMontage> ReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<class UAnimMontage> ReloadWeaponMontage;
	
	// Effect
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties|Effect")
	TObjectPtr<class UParticleSystem> MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties|Effect")
	TObjectPtr<class UParticleSystem> TraceParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties|Effect")
	TObjectPtr<class UParticleSystem> ImpactEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Audio")
	TObjectPtr<class USoundBase> FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Audio")
	TObjectPtr<class USoundBase> HitSound;

	// Properties
protected:
	UPROPERTY(EditAnywhere, Category = "Properties|Fire")
	uint8 AvailableFireMode;
	
	UPROPERTY(EditAnywhere, Category = "Properties|Fire")
	uint8 WeaponID;
	
	UPROPERTY(EditAnywhere, Category = "Properties|Weapon")
	ESOWeaponType WeaponType;
	
	UPROPERTY(EditAnywhere, Category = "Properties|Fire")
	float FireInterval;

	UPROPERTY(EditAnywhere, Category = "Properties|Fire")
	float ReloadInterval;
	
	UPROPERTY(EditAnywhere, Category = "Properties|Fire")
	float ShootingPreparationTime;
	
	UPROPERTY(EditAnywhere, Category = "Properties|Fire")
	float MaxRange;
	
	UPROPERTY(EditAnywhere, Category = "Properties|Damage")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Properties|Damage")
	float HeadShotDamage;

	UPROPERTY(EditAnywhere, Category = "Properties|Recoil")
	float RecoilYaw;

	UPROPERTY(EditAnywhere, Category = "Properties|Recoil")
	float RecoilPitch;

	UPROPERTY(EditAnywhere, Category = "Properties|Recoil")
	float AimedRecoilYaw;

	UPROPERTY(EditAnywhere, Category = "Properties|Recoil")
	float AimedRecoilPitch;
	
	UPROPERTY(EditAnywhere, Category = "Properties|Weapon")
	FName AttachPoint;

	UPROPERTY(EditAnywhere, Category = "Properties|Weapon")
	FName MuzzleSocketName;
	
	// Ammo
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Properties|Ammo")
	int32 ClipSize;
	
	// maximum bullet capacity
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Properties|Ammo")
	int32 MaxAmmoCapacity;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Properties|Ammo")
	uint8 bInfiniteAmmo : 1;
	
	// Input
protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> FireAction;

	/** Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> AimAction;

	/** Precision Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> PrecisionAimAction;

	/** Reload Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> ReloadAction;

	// State
public:
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
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentFireMode(ESOFireMode NewCurrentFireMode) { CurrentFireMode = NewCurrentFireMode; }

	FTimerHandle FireTimerHandle;
	FTimerHandle BurstTimerHandle1;
	FTimerHandle BurstTimerHandle2;
	
	// Data
protected:
	UPROPERTY()
	FSOWeaponStat WeaponStat;

	UPROPERTY()
	FSOWeaponData WeaponData;
	
	// Ammo
protected:
	UPROPERTY()
	TObjectPtr<class USOProjectilePoolComponent> ProjectilePoolComponent; 
	
	TSubclassOf<ASOProjectileBase> AmmoClass; 
};
