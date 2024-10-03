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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION(Category = "SO|Hp")
	void SetCurrentHp(float InHealth);
	
public:
	UFUNCTION(Category = "SO|Hp")
	float GetCurrentHp() const;	

	UFUNCTION(Category = "SO|Hp")
	float GetMaxHP() const;

	float ApplyDamage(float InDamage);
	
	UFUNCTION()
	void OnRep_CurrentHp();

	FOnHpChangedDelegate OnHPChanged;
	FOnHpZeroDelegate OnHpZero;
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHp, Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stat)
	float MaxHP;
};


