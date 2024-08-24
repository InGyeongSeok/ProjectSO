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
