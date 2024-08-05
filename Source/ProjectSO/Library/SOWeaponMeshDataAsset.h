// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SOWeaponMeshDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API USOWeaponMeshDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TArray<USkeletalMesh*> WeaponSkeletalMesh;
};
