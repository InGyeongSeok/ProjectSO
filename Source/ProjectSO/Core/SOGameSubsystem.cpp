// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGameSubsystem.h"

#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Library/SOGunPartsStructLibrary.h"
#include "ProjectSO/Library/SOWeaponDamageDataAsset.h"
#include "ProjectSO/Library/SOWeaponStructLibrary.h"
#include "ProjectSO/Weapon/Projectile/SOProjectilePoolComponent.h"


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
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/Parts/DT_PartsData.DT_PartsData'"));
	if (PartsDataRef.Succeeded())
	{
		PartsDataTable = PartsDataRef.Object;
	}

	// ==========================================
	ConstructorHelpers::FObjectFinder<UDataTable> ScopeStatRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/Parts/DT_ScopeStat.DT_ScopeStat'"));
	if (ScopeStatRef.Succeeded())
	{
		PartsStatTables.Push(ScopeStatRef.Object);		
	}

	ConstructorHelpers::FObjectFinder<UDataTable> MuzzleStatRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/Parts/DT_MuzzleStat.DT_MuzzleStat'"));
	if (MuzzleStatRef.Succeeded())
	{
		PartsStatTables.Push(MuzzleStatRef.Object);		
	}
	
	ConstructorHelpers::FObjectFinder<UDataTable> GripStatRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/Parts/DT_GripStat.DT_GripStat'"));
	if (GripStatRef.Succeeded())
	{
		PartsStatTables.Push(GripStatRef.Object);		
	}

	ConstructorHelpers::FObjectFinder<UDataTable> MagazineStatRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/Parts/DT_MagazineStat.DT_MagazineStat'"));
	if (MagazineStatRef.Succeeded())
	{
		PartsStatTables.Push(MagazineStatRef.Object);		
	}

	ConstructorHelpers::FObjectFinder<UDataTable> StockStatRef(
		TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/Parts/DT_StockStat.DT_StockStat'"));
	if (StockStatRef.Succeeded())
	{
		PartsStatTables.Push(StockStatRef.Object);		
	}

	ProjectilePoolComponentTest = CreateDefaultSubobject<USOProjectilePoolComponent>(TEXT("ProjectilePool"));
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

	// 일치하는 Row가 없음
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

	if(!DamageDataAsset)
	{
		return -1.0f;
	}

	UE_LOG(LogTemp,Log,TEXT("InGunType : %s"), *InGunType);
	//SO_LOG(LogSONetwork,Log,TEXT("%s"),InGunType);
	UE_LOG(LogTemp,Log,TEXT("DamageByHitLocationMap : %f"), DamageDataAsset->DamageByHitLocationMap[InBoneName]);

	return DamageDataAsset->DamageByHitLocationMap[InBoneName];
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

UDataTable* USOGameSubsystem::GetPartsStatTable(int32 idx)
{
	return PartsStatTables[idx];
}

FSOPartsData* USOGameSubsystem::GetPartsData(const uint8 InID)
{
	if (!PartsDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PartsDataTable is not assigned."));
		return nullptr;
	}
	FString RowName = FString::Printf(TEXT("%d"), InID);

	FSOPartsData* PartsDataRow = PartsDataTable->FindRow<FSOPartsData>(FName(*RowName), "");
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

FSOPartsData* USOGameSubsystem::GetPartsData(const ESOGunPartsName InPartsName)
{
	if (!PartsDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PartsDataTable is not assigned."));
		return nullptr;
	}
	FString EnumAsString = UEnum::GetValueAsString<ESOGunPartsName>(InPartsName);
	// "ESOGunPartsName::" 부분 제거
	FString CleanedEnumAsString;
	EnumAsString.Split(TEXT("::"), nullptr, &CleanedEnumAsString);
	
	FString RowName = FString::Printf(TEXT("%s"), *CleanedEnumAsString);

	FSOPartsData* PartsDataRow = PartsDataTable->FindRow<FSOPartsData>(FName(*RowName), "");
	if (PartsDataRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found PartsDataTable for PartsName: %s"), *CleanedEnumAsString);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No PartsDataTable found for PartsName: %s"), *CleanedEnumAsString);
	}
	return PartsDataRow;
}

FSOPartsData* USOGameSubsystem::GetPartsData(const FName InPartsName)
{
	if (!PartsDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PartsDataTable is not assigned."));
		return nullptr;
	}

	FSOPartsData* PartsDataRow = PartsDataTable->FindRow<FSOPartsData>(InPartsName, "");
	if (PartsDataRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found PartsDataTable for Name: %s"), *InPartsName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No PartsDataTable found for Name: %s"), *InPartsName.ToString());
	}
	return PartsDataRow;
}

FSOPartsStat* USOGameSubsystem::GetPartsStat(const uint8 InID, ESOGunPartsType PartsType)
{
	// PartsStatTables
	// 어떤 타입인지 받아서 - 테이블 참조

	// push_back한 순서 
	// PartsType
	UE_LOG(LogTemp, Warning, TEXT("PartsType : %d"), static_cast<int32>(PartsType))
	UDataTable* PartsStatTable = PartsStatTables[static_cast<int32>(PartsType)];
	// PartsStatTable.FindRow<>()
	// PartsStat

	if (!PartsStatTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PartsStatTable is not assigned."));
		return nullptr;
	}

	FString RowName = FString::Printf(TEXT("%d"), InID);
	FSOPartsStat* PartsStatRow = PartsStatTable->FindRow<FSOPartsStat>(FName(*RowName), "");
	
	if (PartsStatRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found PartsStatTable for ID: %d"), InID);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No PartsStatTable found for ID: %d"), InID);
	}
	return PartsStatRow;
}

FSOPartsStat* USOGameSubsystem::GetPartsStat(const ESOGunPartsName InPartsName, ESOGunPartsType PartsType)
{
	UE_LOG(LogTemp, Warning, TEXT("PartsType : %d"), static_cast<int32>(PartsType))
	UDataTable* PartsStatTable = PartsStatTables[static_cast<int32>(PartsType)];

	if (!PartsStatTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PartsStatTable is not assigned."));
		return nullptr;
	}
	
	FString EnumAsString = UEnum::GetValueAsString<ESOGunPartsName>(InPartsName);
	
	FString CleanedEnumAsString;
	EnumAsString.Split(TEXT("::"), nullptr, &CleanedEnumAsString);
	FString RowName = FString::Printf(TEXT("%s"), *CleanedEnumAsString);
	FSOPartsStat* PartsStatRow = PartsStatTable->FindRow<FSOPartsStat>(FName(*RowName), "");
	
	if (PartsStatRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found PartsStatTable for PartsName: %s"), *CleanedEnumAsString);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No PartsStatTable found for PartsName: %s"), *CleanedEnumAsString);
	}
	return PartsStatRow;
}

FSOPartsStat* USOGameSubsystem::GetPartsStat(const FName InPartsName, ESOGunPartsType PartsType)
{
	UE_LOG(LogTemp, Warning, TEXT("PartsType : %d"), static_cast<int32>(PartsType))
	UDataTable* PartsStatTable = PartsStatTables[static_cast<int32>(PartsType)];

	if (!PartsStatTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PartsStatTable is not assigned."));
		return nullptr;
	}

	FSOPartsStat* PartsStatRow = PartsStatTable->FindRow<FSOPartsStat>(InPartsName, "");
	
	if (PartsStatRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found PartsStatTable for Name: %s"), *InPartsName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No PartsStatTable found for ID: %s"), *InPartsName.ToString());
	}
	return PartsStatRow;
}
