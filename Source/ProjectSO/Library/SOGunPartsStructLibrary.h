#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SOGunPartsStructLibrary.generated.h"


enum class ESOGunPartsType;

USTRUCT(BlueprintType)
struct FSOGunPartsBaseData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// FSOGunPartsBaseData();

	// FSOGunPartsBaseData& operator=(const FSOGunPartsBaseData& InOtherStat)

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName PartsName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ESOGunPartsType PartsType;

	// ESO AvailableWeaponType;
};

USTRUCT(BlueprintType)
struct FSOScopeStat : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AimingTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float FOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 bZoomInOut;
};
