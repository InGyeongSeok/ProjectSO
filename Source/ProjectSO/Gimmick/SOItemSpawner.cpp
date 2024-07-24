// Fill out your copyright notice in the Description page of Project Settings.


#include "SOItemSpawner.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectSO/Core/SOGameSubsystem.h"
#include "ProjectSO/Library/SOItemStructLibrary.h"
#include "ProjectSO/Weapon/SOGunBase.h"

class USOGameSubsystem;

ASOItemSpawner::ASOItemSpawner()
{
}

void ASOItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnItem();
}

void ASOItemSpawner::SpawnItem()
{
	Super::SpawnItem();

	int32 SpawnCount = FMath::RandRange(1, MaxSpawnCount);
	
	float MaxX = GetActorLocation().X + Trigger->GetScaledBoxExtent().X;
	float MaxY = GetActorLocation().Y + Trigger->GetScaledBoxExtent().Y;

	float MinX = GetActorLocation().X - Trigger->GetScaledBoxExtent().X;
	float MinY = GetActorLocation().Y - Trigger->GetScaledBoxExtent().Y;
	if (GetSOGameSubsystem())
	{
		int32 TotalSpawnableItem = GetSOGameSubsystem()->GetSpawnableItemCount();
		for (int32 i = 0; i < SpawnCount; ++i)
		{
			int32 SpawnIndex = FMath::RandRange(0, TotalSpawnableItem-1);
			ItemClass = GetSOGameSubsystem()->GetSpawnableItemData(SpawnIndex)->ItemClass;
			AmmoClass= GetSOGameSubsystem()->GetSpawnableItemData(SpawnIndex)->AmmoClass;
			float X = FMath::RandRange(MinX, MaxX);
			float Y = FMath::RandRange(MinY, MaxY);
			FVector SpawnLocation(X, Y, GetActorLocation().Z);

			AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(ItemClass, SpawnLocation, FRotator::ZeroRotator);

			// ASOGunBase* GunActor =Cast<ASOGunBase>(SpawnedItem);
			// if(GunActor &&AmmoClass )
			// {
			// 	AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(ItemClass, SpawnLocation, FRotator::ZeroRotator);
			// }
		}
	}
}

USOGameSubsystem* ASOItemSpawner::GetSOGameSubsystem() const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is not available."));
		return nullptr;
	}

	// 게임 인스턴스 가져오기.
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is not available."));
		return nullptr;
	}

	// 게임 인스턴스에서 서브시스템을 가져오기.
	USOGameSubsystem* SOGameSubsystem = GameInstance->GetSubsystem<USOGameSubsystem>();
	if (!SOGameSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("SOGameSubsystem is not available."));
		return nullptr;
	}

	return SOGameSubsystem;
}

void ASOItemSpawner::SpawnAmmo(int AmmoType)
{
	
}
