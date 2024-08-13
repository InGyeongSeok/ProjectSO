// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SOWeaponDamageDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API USOWeaponDamageDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	 TMap<FString, float> DamageByHitLocationMap;
};
