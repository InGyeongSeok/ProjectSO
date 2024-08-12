// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGameSubsystem.h"

#include "ProjectSO/ProjectSO.h"
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
	TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOWeaponClassAreaDamageData.DT_SOWeaponClassAreaDamageData'"));
	if (WeaponClassAreaDamageRef.Succeeded())
	{
		WeaponClassAreaDamageTable = WeaponClassAreaDamageRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> HitAreaDamageRef(
TEXT("/Script/Engine.DataTable'/Game/StellarObsidian/GameData/DT_SOHitAreaDamageData.DT_SOHitAreaDamageData'"));
	if (HitAreaDamageRef.Succeeded())
	{
		HitAreaDamageTable = HitAreaDamageRef.Object;
	}
}

void USOGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("Initialize "));

	ProcessWeaponDamageDataRows();
	LoadHitAreaDamageMap();
	LoadWeaponClassAreaDamageMap();
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
	if (HitAreaDamageMap.IsEmpty())
	{
		// 에러 발생
		return -1.0f;
	}
	if (const float* FoundValue = HitAreaDamageMap.Find(Area))
	{
		return *FoundValue;
	}
	// 에러 발생
	return -1.0f;
}

float USOGameSubsystem::GetHitAreaDamage(const FString& GunType, const FString& Area) const
{
	if (WeaponClassAreaDamageMap.IsEmpty())
	{
		// 에러 발생
		return -1.0f;
	}
	// GunType으로 FAreaDamageMap 찾기
	const FAreaDamageMap* AreaDamageMap = WeaponClassAreaDamageMap.Find(GunType);
	if (AreaDamageMap)
	{
		// Area로 데미지 값 찾기
		if (const float* FoundValue = AreaDamageMap->DamageMap.Find(Area))
		{
			return *FoundValue;
		}
		else
		{
			// Area가 존재하지 않음
			UE_LOG(LogSOSubsystem, Warning, TEXT("Area '%s' not found for GunType '%s'"), *Area, *GunType);
			return -1.0f;
		}
	}
	else
	{
		// GunType이 존재하지 않음
		UE_LOG(LogSOSubsystem, Warning, TEXT("GunType '%s' not found in WeaponClassAreaDamageMap"), *GunType);
		return -1.0f;
	}
}

//Initialize 에서 ProcessWeaponDamageDataRows 호출
//이 함수는 Weapon Damage by bone 에 대한 정보를 가져온다. (파싱?)
void USOGameSubsystem::ProcessWeaponDamageDataRows() 
{
	if (!WeaponDamageTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("No WeaponDamageTable found "));

		return;
	}
	TArray<FName> RowNames = WeaponDamageTable->GetRowNames();
	int32 NumDamageDataRows = RowNames.Num();

	for (int32 ID = 0; ID < NumDamageDataRows; ++ID)
	{
		FSOWeaponDamageData* DamageDataTable = GetWeaponDamageData(ID); //행 가져오기 

		if (DamageDataTable)
		{
			for (TFieldIterator<FProperty> It(FSOWeaponDamageData::StaticStruct()); It; ++It)
			{
				FProperty* Property = *It;
				FString PropertyName = Property->GetName();
				FString PropertyValue;
				// Property Value 값 넣어주기 
				Property->ExportText_InContainer(0, PropertyValue, DamageDataTable, DamageDataTable, nullptr, PPF_None);
				InitializeWeaponDamageByBoneTable( ID, PropertyName ,PropertyValue);
			}
		}
	}
}

//WeaponDamageByBoneTable에 실질적인 데이터 Setting 진행 
void USOGameSubsystem::InitializeWeaponDamageByBoneTable(const int32 InID , const FString& InBoneName, const FString& InDamageValue)
{
	if(!WeaponDamageByBoneTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("No WeaponDamageByBoneTable found "));
		return ; 
	}
	
	FString RowName = FString::Printf(TEXT("%d"), InID);

	FSOWeaponDamageByBone* WeaponDamageByBoneDataRow = WeaponDamageByBoneTable->FindRow<FSOWeaponDamageByBone>(
		FName(*RowName), "");
	if (WeaponDamageByBoneDataRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found WeaponDamageByBoneTable for ID: %d"), InID);
		float InDamageFloatValue = FCString::Atof(*InDamageValue);
		WeaponDamageByBoneDataRow->DamageByHitLocationMap.Add(InBoneName,InDamageFloatValue);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No WeaponDamageByBoneTable found for ID: %d"), InID);
	}
}

void USOGameSubsystem::LoadHitAreaDamageMap()
{
	if(!HitAreaDamageTable)
	{
		return;
	}
	HitAreaDamageMap.Empty();
	TArray<FName> RowNames = HitAreaDamageTable->GetRowNames();
	int32 NumDamageDataRows = RowNames.Num();
	
	for (int32 ID = 0; ID < NumDamageDataRows; ++ID)
	{
		// 행의 데이터를 가져옴
		FSOHitAreaDamageData* HitAreaDamageData = HitAreaDamageTable->FindRow<FSOHitAreaDamageData>(RowNames[ID], TEXT(""));

		if (HitAreaDamageData)
		{
			// 구조체의 모든 프로퍼티를 순회
			for (TFieldIterator<FProperty> It(FSOHitAreaDamageData::StaticStruct()); It; ++It)
			{
				FProperty* Property = *It;
				FString PropertyName = Property->GetName();
				FString PropertyValue;

				// Property Value 값을 가져옴
				Property->ExportText_InContainer(0, PropertyValue, HitAreaDamageData, HitAreaDamageData, nullptr, PPF_None);

				// Property Value를 float로 변환하고 HitAreaDamageMap에 추가
				float DamageValue = FCString::Atof(*PropertyValue);
				HitAreaDamageMap.Add(PropertyName, DamageValue);
			}
		}
	}
	for (const auto& Pair : HitAreaDamageMap)
	{
		UE_LOG(LogSOSubsystem, Log, TEXT("Bone: %s, Damage: %f"), *Pair.Key, Pair.Value);
	}
}

void USOGameSubsystem::LoadWeaponClassAreaDamageMap()
{
	if(!WeaponClassAreaDamageTable)
	{
		return;
	}
	WeaponClassAreaDamageMap.Empty();
	TArray<FName> RowNames = WeaponClassAreaDamageTable->GetRowNames();
	int32 NumDamageDataRows = RowNames.Num();
	for (int32 ID = 0; ID < NumDamageDataRows; ++ID)
	{
		// 행의 데이터를 가져옴
		FSOWeaponClassAreaDamageData* WeaponClassAreaDamageData = WeaponClassAreaDamageTable->FindRow<FSOWeaponClassAreaDamageData>(RowNames[ID], TEXT(""));

		if (WeaponClassAreaDamageData)
		{
			FAreaDamageMap AreaDamageMap;
			// 구조체의 모든 프로퍼티를 순회
			for (TFieldIterator<FProperty> It(FSOWeaponClassAreaDamageData::StaticStruct()); It; ++It)
			{
				FProperty* Property = *It;
				FString PropertyName = Property->GetName();

				if (PropertyName == "WeaponType")
				{
					continue;
				}

				FString PropertyValue;

				// Property Value 값을 가져옴
				Property->ExportText_InContainer(0, PropertyValue, WeaponClassAreaDamageData, WeaponClassAreaDamageData, nullptr, PPF_None);

				// Property Value를 float로 변환하고 FAreaDamageMap에 추가
				float DamageValue = FCString::Atof(*PropertyValue);
				AreaDamageMap.DamageMap.Add(PropertyName, DamageValue);
			}
			// WeaponClass 이름으로 WeaponClassAreaDamageMap에 추가
			FString WeaponClassName = UEnum::GetDisplayValueAsText(WeaponClassAreaDamageData->WeaponType).ToString();
			WeaponClassAreaDamageMap.Add(WeaponClassName, AreaDamageMap);
		}
	}
	// 확인을 위해 WeaponClassAreaDamageMap 출력
	for (const auto& WeaponClassPair : WeaponClassAreaDamageMap)
	{
		UE_LOG(LogSOSubsystem, Log, TEXT("Weapon Class: %s"), *WeaponClassPair.Key);
		for (const auto& DamagePair : WeaponClassPair.Value.DamageMap)
		{
			UE_LOG(LogSOSubsystem, Log, TEXT("  Bone: %s, Damage: %f"), *DamagePair.Key, DamagePair.Value);
		}
	}
}
