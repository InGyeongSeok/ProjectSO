// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectSO/Library/SOWeaponStructLibrary.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SOGameSubsystem.generated.h"

struct FSOSpawnableItemClasses;
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
	uint32 GetSpawnableItemCount() const {return TotalSpawnableItem; };
	float GetHitAreaDamage(const FString& Key) const;

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

	UPROPERTY()
	TMap<FString, float> HitAreaDamageMap;

	//DT_SOWeaponDamageByBone


	UPROPERTY()
	uint32 TotalSpawnableItem;
	
	void ProcessWeaponDamageDataRows();
	void InitializeWeaponDamageByBoneTable(const int32 InID , const FString& InBoneName, const FString& InPropertyValue);

	void MakeHitAreaDamageMap();
};
