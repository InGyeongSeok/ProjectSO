
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NiagaraSystem.h"
#include "SOWeaponData.generated.h"


enum class EWeaponType;

USTRUCT(BlueprintType)
struct FSOWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<UAnimMontage> AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	TObjectPtr<UNiagaraSystem> MuzzleFlashEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Socket)
	FVector SocketLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Socket)
	FVector SocketRotation;
	
};