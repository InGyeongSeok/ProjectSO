#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NiagaraSystem.h"
#include "SOWeaponEnumLibrary.h"
#include "SOWeaponStructLibrary.generated.h"


class ASOProjectileBase;

USTRUCT(BlueprintType)
struct FSOWeaponStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSOWeaponStat(): WeaponType(ESOWeaponType::Pistol), FireMode(0), AmmoType(0), FireInterval(0), ReloadInterval(0), QuickReloadInterval(0),
					 Speed(0),
					 MaxRange(0),
					 Damage(0),
					 HeadShotDamage(0),
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
			Damage = InOhterStat.Damage;
			HeadShotDamage = InOhterStat.HeadShotDamage;
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
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float HeadShotDamage;

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
			SkeletalMesh = InOhterStat.SkeletalMesh;
			FireMontage =  InOhterStat.FireMontage;
			EquipMontage = InOhterStat.EquipMontage;
			ReloadMontage = InOhterStat.ReloadMontage;
			ReloadWeaponMontage = InOhterStat.ReloadWeaponMontage;
			MuzzleFlashEffect = InOhterStat.MuzzleFlashEffect;
			EjectShellParticles = InOhterStat.EjectShellParticles;
			FireSound = InOhterStat.FireSound;
			EquipSocketName= InOhterStat.EquipSocketName;
			MuzzleSocketName= InOhterStat.MuzzleSocketName;

		}
		return *this;
	}
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID)
	uint8 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TSubclassOf<ASOProjectileBase> AmmoClass; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponType)
	ESOWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationState)
	EALSOverlayState OverlayState;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMesh> SkeletalMesh;

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
};