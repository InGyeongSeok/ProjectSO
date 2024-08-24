// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGameSubsystem.h"

#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Library/SOGunPartsStructLibrary.h"
#include "ProjectSO/Library/SOWeaponDamageDataAsset.h"
#include "ProjectSO/Library/SOWeaponStructLibrary.h"


USOGameSubsystem::USOGameSubsystem()
{
	ConstructorHelpers::FObjectFinder<UDataTable> WeaponDataRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOWeaponDataTable.DT_SOWeaponDataTable'"));
	if (WeaponDataRef.Succeeded())
	{
		WeaponDataTable = WeaponDataRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> WeaponStatRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOWeaponStatTable.DT_SOWeaponStatTable'"));
	if (WeaponStatRef.Succeeded())
	{
		WeaponStatTable = WeaponStatRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> SpanwableDataRef(
		TEXT(
			"/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOSpanwnableItemClasses.DT_SOSpanwnableItemClasses'"));
	if (SpanwableDataRef.Succeeded())
	{
		SpawnableItemDataTable = SpanwableDataRef.Object;
		TArray<FName> RowNames = SpawnableItemDataTable->GetRowNames();
		TotalSpawnableItem = RowNames.Num();
	}

	ConstructorHelpers::FObjectFinder<UDataTable> WeaponDamageDataRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOWeaponDamageData.DT_SOWeaponDamageData'"));
	if (WeaponDamageDataRef.Succeeded())
	{
		WeaponDamageTable = WeaponDamageDataRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> WeaponDamageByBoneRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOWeaponDamageByBone.DT_SOWeaponDamageByBone'"));
	if (WeaponDamageDataRef.Succeeded())
	{
		WeaponDamageByBoneTable = WeaponDamageByBoneRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> WeaponClassAreaDamageRef(
	TEXT("Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOWeaponClassAreaDamageData.DT_SOWeaponClassAreaDamageData'"));
	if (WeaponClassAreaDamageRef.Succeeded())
	{
		WeaponClassAreaDamageTable = WeaponClassAreaDamageRef.Object;
	}
///Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOWeaponClassAreaDamageData.DT_SOWeaponClassAreaDamageData'
	ConstructorHelpers::FObjectFinder<UDataTable> HitAreaDamageRef(
	TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOHitAreaDamageData.DT_SOHitAreaDamageData'"));
	if (HitAreaDamageRef.Succeeded())
	{
		HitAreaDamageTable = HitAreaDamageRef.Object;
	}

	ConstructorHelpers::FObjectFinder<USOProjectileHitEffectDataAsset> ProjectileHitEffectDataAssetRef(
TEXT("/Script/ProjectSO.SOProjectileHitEffectDataAsset'/Game/StellarObsidian/GameData/DataAsset/DA_SurfaceEffect.DA_SurfaceEffect'"));
	if (ProjectileHitEffectDataAssetRef.Succeeded())
	{
		ProjectileHitEffectDataAsset = ProjectileHitEffectDataAssetRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> PartsDataRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_PartsData.DT_PartsData'"));
	if (PartsDataRef.Succeeded())
	{
		PartsDataTable = PartsDataRef.Object;
	}
	
}

void USOGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("Initialize "));

	//ProcessWeaponDamageDataRows();
	//LoadHitAreaDamageMap();
	//LoadWeaponClassAreaDamageMap();
}

USOGameSubsystem* USOGameSubsystem::GetSOGameSubsystem()
{
	if (GetWorld())
	{
		if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
		{
			return GameInstance->GetSubsystem<USOGameSubsystem>();
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

FSOWeaponDamageData* USOGameSubsystem::GetWeaponDamageData(const uint8 InID)
{
	if (!WeaponDamageTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponDamageTable is not assigned."));
		return nullptr;
	}

	FString RowName = FString::Printf(TEXT("%d"), InID);

	FSOWeaponDamageData* WeaponDamageDataRow = WeaponDamageTable->FindRow<FSOWeaponDamageData>(FName(*RowName), "");
	if (WeaponDamageDataRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found WeaponDamageTable for ID: %d"), InID);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No WeaponDamageTable found for ID: %d"), InID);
	}
	return WeaponDamageDataRow;
}

FSOSpawnableItemClasses* USOGameSubsystem::GetSpawnableItemData(const int32 InIndex)
{
	if (!SpawnableItemDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponDataTable is not assigned."));
		return nullptr;
	}

	FString RowName = FString::Printf(TEXT("%d"), InIndex);

	FSOSpawnableItemClasses* SpawnableDataRow = SpawnableItemDataTable->FindRow<FSOSpawnableItemClasses>(
		FName(*RowName), "");
	if (SpawnableDataRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found WeaponDataTable for ID: %d"), InIndex);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No WeaponDataTable found for ID: %d"), InIndex);
	}
	return SpawnableDataRow;
}

float USOGameSubsystem::GetHitAreaDamage(const FString& Area) const
{
	if (!IsValid(HitAreaDamageTable))
	{
		// 에러 발생
		return -1.0f;
	}
	
	FSOHitAreaDamageData* HitAreaDamageDataRow = HitAreaDamageTable->FindRow<FSOHitAreaDamageData>(
		FName(*Area), "");

	if(!HitAreaDamageDataRow)
	{
		return -1.0f;
	}

	return HitAreaDamageDataRow->ReflectRate;
}

float USOGameSubsystem::GetWeaponClassAreaDamage(const FString& InGunType, const FString& InBoneName) const
{
	if(!WeaponClassAreaDamageTable)
	{
		return -1.0f; 
	}
	FSOWeaponClassAreaDamageData* WeaponClassAreaDamage = WeaponClassAreaDamageTable->FindRow<FSOWeaponClassAreaDamageData>(FName(InGunType), "");

	if(!WeaponClassAreaDamage)
	{
		return -1.0f; 
	}
	//WeaponBoneDamageDataAsset
	const USOWeaponDamageDataAsset* DamageDataAsset = WeaponClassAreaDamage->WeaponBoneDamageDataAsset;
		// WeaponClassAreaDamage->WeaponBoneDamageDataAsset;

	if(!DamageDataAsset)
	{
		return -1.0f;
	}

	UE_LOG(LogTemp,Log,TEXT("InGunType : %s"), *InGunType);
	//SO_LOG(LogSONetwork,Log,TEXT("%s"),InGunType);
	UE_LOG(LogTemp,Log,TEXT("DamageByHitLocationMap : %f"), DamageDataAsset->DamageByHitLocationMap[InBoneName]);

	return  DamageDataAsset->DamageByHitLocationMap[InBoneName];
	//return -1;
}

USOProjectileHitEffectDataAsset* USOGameSubsystem::GetProjectileHitEffectDataAsset() const
{
	return ProjectileHitEffectDataAsset;
}

UNiagaraSystem* USOGameSubsystem::GetSurfaceEffect(const TArray<FName>& ActorTags)
{
	UNiagaraSystem* SelectedEffect;
	for (const FName& Tag : ActorTags)
	{
		// SO_LOG(LogSOProjectileBase, Log, TEXT("Tag : %s"), *Tag.ToString())
		if (ProjectileHitEffectDataAsset->EffectBySurface.Contains(Tag))
		{
			SelectedEffect = ProjectileHitEffectDataAsset->EffectBySurface[Tag];
			if(SelectedEffect)
			{
				UE_LOG(LogTemp, Log, TEXT("SelectedEffect : %s"), *SelectedEffect->GetName())
				return SelectedEffect;
			}
			UE_LOG(LogTemp, Log, TEXT("SelectedEffect is Null"))			
		}		
		break;
	}
	return nullptr;
}

FSOGunPartsBaseData* USOGameSubsystem::GetPartsData(const uint8 InID)
{
	if (!PartsDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PartsDataTable is not assigned."));
		return nullptr;
	}

	FString RowName = FString::Printf(TEXT("%d"), InID);

	FSOGunPartsBaseData* PartsDataRow = PartsDataTable->FindRow<FSOGunPartsBaseData>(FName(*RowName), "");
	if (PartsDataRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found PartsDataTable for ID: %d"), InID);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No PartsDataTable found for ID: %d"), InID);
	}
	return PartsDataRow;
}