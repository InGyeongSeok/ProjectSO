// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "SOHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API USOHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()
public:
	USOHealthComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Category = "SO|Health")
	float GetHealth() const;

	UFUNCTION(Category = "SO|Health")
	void SetHealth(float InHealth);

	UFUNCTION(Category = "SO|Health")
	float GetMaxHealth() const;
	
protected:
	UPROPERTY()
	float Health;

	UPROPERTY()
	float MaxHealth;
};


