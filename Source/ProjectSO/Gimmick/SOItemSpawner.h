// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOSpawnerBase.h"
#include "SOItemSpawner.generated.h"

class USOGameSubsystem;
/**
 * 
 */
UCLASS()
class PROJECTSO_API ASOItemSpawner : public ASOSpawnerBase
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ASOItemSpawner();

protected:
	virtual void BeginPlay() override;

protected:
	virtual void SpawnItem() override;

	//스폰 가능한 아이템의  총 개수를 가져오기
	USOGameSubsystem* GetSOGameSubsystem()const;

	//총알 스폰
	void SpawnAmmo(int AmmoType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TSubclassOf<AActor> AmmoClass; // 여기에 블루프린트 클래스를 담습니다.


};
