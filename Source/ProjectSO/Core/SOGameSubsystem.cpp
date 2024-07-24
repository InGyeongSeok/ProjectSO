// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGameSubsystem.h"

#include "ProjectSO/Library/SOWeaponStructLibrary.h"

USOGameSubsystem::USOGameSubsystem()
{
	ConstructorHelpers::FObjectFinder<UDataTable> WeaponDataRef(TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOWeaponDataTable.DT_SOWeaponDataTable'"));
	if (WeaponDataRef.Succeeded())
	{
		WeaponDataTable = WeaponDataRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> WeaponStatRef(TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOWeaponStatTable.DT_SOWeaponStatTable'"));
	if (WeaponStatRef.Succeeded())
	{
		WeaponStatTable = WeaponStatRef.Object;
	}
}

void USOGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

USOGameSubsystem* USOGameSubsystem::GetSOGameSubsystem(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		if (const UWorld* World = WorldContextObject->GetWorld())
		{
			if (UGameInstance* GameInstance = World->GetGameInstance())
			{
				return GameInstance->GetSubsystem<USOGameSubsystem>();
			}
		}
	}
	return nullptr;
}

FSOWeaponStat* USOGameSubsystem::GetWeaponStatData(const uint8 InID)
{
	if (!WeaponStatTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponStatTable is not assigned."));
		return nullptr;
	}

	FString RowName = FString::Printf(TEXT("%d"), InID);
	
	FSOWeaponStat* WeaponStatDataRow = WeaponStatTable->FindRow<FSOWeaponStat>(FName(*RowName), "");
	if (WeaponStatDataRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found WeaponStatData for ID: %d"), InID);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No WeaponStatData found for ID: %d"), InID);
	}
	return WeaponStatDataRow;
}

FSOWeaponData* USOGameSubsystem::GetWeaponData(const uint8 InID)
{
	if (!WeaponDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponDataTable is not assigned."));
		return nullptr;
	}

	FString RowName = FString::Printf(TEXT("%d"), InID);
	
	FSOWeaponData* WeaponDataRow = WeaponDataTable->FindRow<FSOWeaponData>(FName(*RowName), "");
	if (WeaponDataRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found WeaponDataTable for ID: %d"), InID);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No WeaponDataTable found for ID: %d"), InID);
	}
	return WeaponDataRow;
}


