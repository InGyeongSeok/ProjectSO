// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectSO/Library/SOWeaponStructLibrary.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SOGameSubsystem.generated.h"

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

	//GetFuntions
	USOGameSubsystem* GetSOGameSubsystem(const UObject* WorldContextObject);
	
	FSOWeaponStat* GetWeaponStatData(const uint8 InID);
	FSOWeaponData* GetWeaponData(const uint8 InID);


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<UDataTable> WeaponDataTable;


	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<UDataTable> WeaponStatTable;

	
	
};
