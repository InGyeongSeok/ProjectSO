#pragma once

#include "CoreMinimal.h"
#include "SOWeaponEnumLibrary.h"
#include "Engine/DataTable.h"
#include "SOGunPartsStructLibrary.generated.h"


enum class ESOGunPartsType;

USTRUCT(BlueprintType)
struct FSOGunPartsBaseData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FSOGunPartsBaseData& operator=(const FSOGunPartsBaseData& InOtherData)
	{
		if(this != &InOtherData)
		{
			ID = InOtherData.ID;
			PartsType = InOtherData.PartsType;
			PartsMesh = InOtherData.PartsMesh;
			OffsetMapping = InOtherData.OffsetMapping;
		}
		return *this;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ID)
	uint8 ID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Type)
	ESOGunPartsType PartsType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMesh> PartsMesh; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Offset)
	TMap<FName, FTransform> OffsetMapping;
};

USTRUCT(BlueprintType)
struct FSOPartsStat : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Info)
	uint8 ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Info)
	FName PartsName;
	/* MuzzleAttachment */
	// 총구 화염 은폐율
	// -100% = 완전히 가림
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat|Muzzle")
	float HideMuzzleFlash;

	/* MuzzleAttachment , Grip */
	// 수평 반동
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat|Recoil")
	float YawRecoilReduction;

	// 수직 반동
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat|Recoil")
	float PitchRecoilReduction;

	/* Scope, Grip, Stock */
	// 정조준 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat|Aim")
	float AimingRate;

	/* Scope */
	// 배율
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat|Aim")
	float FOV;

	// 가변 배율 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat|Aim")
	uint8 bZoomInOut;
	
	/* Magazine */
	// 재장전 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat|Reload")
	float ReloadRate;
	
	// 대탄 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stat|Reload")
	uint8 bLargeClip;

	// 탄알 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat|Reload")
	ESOAmmoType AmmoType;
};