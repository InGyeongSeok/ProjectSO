// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectSO/Library/SOGunPartsStructLibrary.h"
#include "ProjectSO/Library/SOItemStructLibrary.h"
#include "ProjectSO/Library/SOWeaponStructLibrary.h"
#include "ProjectSO/Library/SOItemStructLibrary.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ProjectSO/Library/SOProjectileHitEffectDataAsset.h"
#include "SOGameSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FAreaDamageMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, float> DamageMap;
};

/**
 * 
 */
UCLASS()
class PROJECTSO_API USOGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	USOGameSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	//Getters
	USOGameSubsystem* GetSOGameSubsystem();
	FSOWeaponStat* GetWeaponStatData(const uint8 InID);
	FSOWeaponData* GetWeaponData(const uint8 InID);
	FSOWeaponDamageData* GetWeaponDamageData(const uint8 InID);
	FSOSpawnableItemClasses* GetSpawnableItemData(const int32 InIndex);
	FSOGunPartsBaseData* GetPartsData(const uint8 InID);
	FSOPartsStat* GetPartsStat(const uint8 InID, ESOGunPartsType PartsType);
	uint32 GetSpawnableItemCount() const {return TotalSpawnableItem; }
	float GetHitAreaDamage(const FString& Area) const;
	float GetWeaponClassAreaDamage(const FString& InGunType, const FString& InBoneName)  const;
	USOProjectileHitEffectDataAsset* GetProjectileHitEffectDataAsset() const; 
	UNiagaraSystem* GetSurfaceEffect(const TArray<FName>& ActorTags);

	FSOWeaponStat* CalculateWeaponStat(FSOEquippedPartsInfo InPartsInfo, uint8 WeaponID);

	UDataTable* GetPartsStatTable(int32 idx);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDataTable> WeaponDataTable;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDataTable> WeaponStatTable;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDataTable> WeaponDamageTable;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDataTable> SpawnableItemDataTable;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDataTable> WeaponDamageByBoneTable;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDataTable> WeaponClassAreaDamageTable;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDataTable> HitAreaDamageTable;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDataTable> PartsDataTable;

	// UPROPERTY(BlueprintReadOnly)
	// TObjectPtr<UDataTable> PartsStatTable;

	UPROPERTY(BlueprintReadOnly)
	TArray<UDataTable*> PartsStatTables;

	UPROPERTY()
	TObjectPtr<USOProjectileHitEffectDataAsset> ProjectileHitEffectDataAsset;
	
	UPROPERTY()
	uint32 TotalSpawnableItem;

};
