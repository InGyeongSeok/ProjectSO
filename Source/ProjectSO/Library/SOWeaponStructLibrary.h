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
	FSOWeaponStat(): WeaponType(EWeaponType::Pistol), FireMode(0), AmmoType(0), FireInterval(0), ReloadInterval(0), QuickReloadInterval(0),
					 Speed(0),
					 MaxRange(0),
					 Damage(0),
					 HeadShotDamage(0),
					 AimedRecoilYaw(0), AimedRecoilPitch(0),
					 ClipSize(0),
					 LargeClipSize(0)
	{
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	uint8 ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	FName WeaponName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	EWeaponType WeaponType;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	uint8 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	TObjectPtr<UNiagaraSystem> MuzzleFlashEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Socket)
	FVector SocketLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Socket)
	FVector SocketRotation;
	
};