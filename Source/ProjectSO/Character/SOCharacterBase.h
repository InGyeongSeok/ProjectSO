// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "ProjectSO/Weapon/SOGunBase.h"
#include "SOCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API ASOCharacterBase : public AALSCharacter
{
	GENERATED_BODY()

public:
	ASOCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SO|Equip")
	TObjectPtr<ASOGunBase> CurrentWeapon;
	
public:
	// 나중에 장착 가능한 것들만 모아서 하기
	UFUNCTION(BlueprintCallable, Category = "SO|Equip")
	void EquipGun(ASOGunBase* Equipment);

	/** Input */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SO|Input")
	void AttackAction(bool bValue);
};
