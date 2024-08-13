// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SOProjectileHitEffectDataAsset.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class PROJECTSO_API USOProjectileHitEffectDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, UNiagaraSystem*> EffectBySurface;
};
