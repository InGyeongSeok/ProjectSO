// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectSO/Library/SOWeaponEnumLibrary.h"
#include "ProjectSO/Library/SOWeaponStructLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "ProjectSO/Interface/SODamageableInterface.h"
#include "ProjectSO/Interface/SOEquippableInterface.h"
#include "SOGunBase.generated.h"

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

	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Owner
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	TObjectPtr<class ASOCharacterBase> OwningCharacter;

	// Component
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCapsuleComponent> CollisionComp;
	
	// Montage
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	TObjectPtr<class UAnimMontage> EquipMontage;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	TObjectPtr<class UAnimMontage> FireMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	TObjectPtr<class UAnimMontage> ReloadMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	TObjectPtr<class UAnimMontage> ReloadWeaponMontage;
	
	// Effect
protected:
	UPROPERTY(EditAnywhere, Category = "Properties|Effect")
	TObjectPtr<class UParticleSystem> MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Properties|Effect")
	TObjectPtr<class UParticleSystem> TraceParticles;

	UPROPERTY(EditAnywhere, Category = "Properties|Effect")
	TObjectPtr<class UParticleSystem> ImpactEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Audio")
	TObjectPtr<class USoundBase> FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Audio")
	TObjectPtr<class USoundBase> HitSound;

	// Properties
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Fire")
	uint8 FireMode;
	
	UPROPERTY(EditAnywhere, Category = "Properties|Fire")
	uint8 WeaponID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Weapon")
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Weapon")
	FName AttachPoint;

	// Ammo
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "Properties|Ammo")
	int32 ClipSize;
	
	// maximum bullet capacity
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "Properties|Ammo")
	int32 MaxAmmoCapacity;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "Properties|Ammo")
	uint8 bInfiniteAmmo : 1;
	
	// Input
public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> FireAction;

	/** Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AimAction;

	/** Precision Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PrecisionAimAction;

	/** Reload Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
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
	
	//  Data
protected:
	UPROPERTY()
	FSOWeaponStat WeaponStat;

	UPROPERTY()
	FSOWeaponData WeaponData; 

	/** IDamageable **/
public:
	virtual void PressLMB() override;
	virtual void ReleaseLMB() override;

	/** IEquippableInterface **/
public:
	virtual EALSOverlayState GetOverlayState() const override;

	// Fire Logic
protected:
	virtual void OnFire();
	virtual void AutoFire();
	virtual void BurstFire();
	virtual void SingleFire();
	virtual void FireProjectile();
	virtual void CreateProjectile(FVector StartPosition, FRotator StartRotation);
	virtual void StopFire();

	// Effect
protected:
	virtual void ShowEffect(FVector StartPosition, FRotator StartRotation);
	virtual void PlaySound();
	virtual void Recoil();

protected:
	virtual void Reload();
	virtual void Aim();
public:
	virtual void Equip();

	//Data Settings
protected:
	void SetGunData(const uint8 InID);

	// multi
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(Server, Unreliable)
	void ServerRPCOnFire(FVector StartPosition, FRotator StartRotation);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCShowEffect(FVector StartPosition, FRotator StartRotation);


};
