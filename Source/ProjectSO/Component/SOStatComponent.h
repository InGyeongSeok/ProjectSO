// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SOStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate)
//DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*Current HP*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHpChangedDelegate, float /*CurrentHp*/, float /*MaxHp*/)
/**
 * 
 */
UCLASS()
class PROJECTSO_API USOStatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	USOStatComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Category = "SO|Hp")
	float GetCurrentHp() const;

	UFUNCTION(Category = "SO|Hp")
	void SetCurrentHp(float InHealth);

	UFUNCTION(Category = "SO|Hp")
	float GetMaxHP() const;

	float ApplyDamage(float InDamage);	

	FOnHpChangedDelegate OnHPChanged;
	FOnHpZeroDelegate OnHpZero;
	
protected:
	UPROPERTY()
	float CurrentHp;

	UPROPERTY()
	float MaxHP;
};


