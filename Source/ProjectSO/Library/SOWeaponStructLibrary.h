#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NiagaraSystem.h"
#include "SOWeaponEnumLibrary.h"
#include "SOWeaponStructLibrary.generated.h"



USTRUCT(BlueprintType)
struct FSOWeaponStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSOWeaponStat(): WeaponType(ESOWeaponType::Pistol), FireMode(0), AmmoType(0), FireInterval(0), ReloadInterval(0), QuickReloadInterval(0),
					 Speed(0),
					 MaxRange(0),
					 AimedRecoilYaw(0), AimedRecoilPitch(0),
					 ClipSize(0),
					 LargeClipSize(0)
	{
	}

	FSOWeaponStat& operator=(const FSOWeaponStat& InOhterStat)
	{
		if(this!= &InOhterStat)
		{
			ID = InOhterStat.ID;
			WeaponName = InOhterStat.WeaponName;
			WeaponType = InOhterStat.WeaponType;
			FireMode = InOhterStat.FireMode;
			AmmoType = InOhterStat.AmmoType;
			FireInterval = InOhterStat.FireInterval;
			ReloadInterval = InOhterStat.ReloadInterval;
			QuickReloadInterval = InOhterStat.QuickReloadInterval;
			Speed = InOhterStat.Speed;
			MaxRange = InOhterStat.MaxRange;
			RecoilYaw = InOhterStat.RecoilYaw;
			RecoilPitch = InOhterStat.RecoilPitch;
			AimedRecoilYaw = InOhterStat.AimedRecoilYaw;
			AimedRecoilPitch = InOhterStat.AimedRecoilPitch;
			ClipSize = InOhterStat.ClipSize;
			LargeClipSize = InOhterStat.LargeClipSize;
		}
		return *this;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	uint8 ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	FName WeaponName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	ESOWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int FireMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float FireInterval;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float ReloadInterval;
    	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float QuickReloadInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float RecoilYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float RecoilPitch;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AimedRecoilYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AimedRecoilPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int ClipSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int LargeClipSize;


};


USTRUCT(BlueprintType)
struct FSOWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSOWeaponData& operator=(const FSOWeaponData& InOhterStat)
	{
		if(this!= &InOhterStat)
		{
			ID = InOhterStat.ID;
			AmmoClass=InOhterStat.AmmoClass;
			WeaponType = InOhterStat.WeaponType;
			OverlayState = InOhterStat.OverlayState;
			WeaponMeshDataAsset = InOhterStat.WeaponMeshDataAsset;
			FireMontage =  InOhterStat.FireMontage;
			EquipMontage = InOhterStat.EquipMontage;
			ReloadMontage = InOhterStat.ReloadMontage;
			ReloadWeaponMontage = InOhterStat.ReloadWeaponMontage;
			MuzzleFlashEffect = InOhterStat.MuzzleFlashEffect;
			EjectShellParticles = InOhterStat.EjectShellParticles;
			FireSound = InOhterStat.FireSound;
			EquipSocketName= InOhterStat.EquipSocketName;
			MuzzleSocketName= InOhterStat.MuzzleSocketName;
			FireEffectSocketName= InOhterStat.FireEffectSocketName;

		}
		return *this;
	}
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID)
	uint8 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TSubclassOf<class ASOProjectileBase> AmmoClass; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponType)
	ESOWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationState)
	EALSOverlayState OverlayState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class USOWeaponMeshDataAsset> WeaponMeshDataAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> ReloadWeaponMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	TObjectPtr<UParticleSystem> MuzzleFlashEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effect)
	TObjectPtr<class UNiagaraSystem> EjectShellParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
	TObjectPtr<class USoundBase> FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Socket)
	FName EquipSocketName; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Socket)
	FName MuzzleSocketName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Socket)
	FName FireEffectSocketName; 
};



USTRUCT(BlueprintType)
struct FSOWeaponDamageData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FSOWeaponDamageData(): Head(0), Neck(0), Clavicles(0), Upperchest(0), Lowerchest(0),
				 Stomach(0),
				 Pelvis(0),
				 Upperlimb(0), Lowerlimb(0),
				 Handfoot(0)
	{
	}
	
	FSOWeaponDamageData& operator=(const FSOWeaponDamageData& InOhterDamageData)
	{
		if(this!= &InOhterDamageData)
		{
			ID = InOhterDamageData.ID;
			Head = InOhterDamageData.Head;
			Neck = InOhterDamageData.Neck;
			Clavicles = InOhterDamageData.Clavicles;
			Upperchest =  InOhterDamageData.Upperchest;
			Lowerchest = InOhterDamageData.Lowerchest;
			Stomach = InOhterDamageData.Stomach;
			Pelvis = InOhterDamageData.Pelvis;
			Upperlimb = InOhterDamageData.Upperlimb;
			Lowerlimb = InOhterDamageData.Lowerlimb;
			Handfoot = InOhterDamageData.Handfoot;
		}
		return *this;
	}
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	uint8 ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Neck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Clavicles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Upperchest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Lowerchest;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Stomach;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Pelvis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Upperlimb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Lowerlimb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponDamage)
	float Handfoot;
};
