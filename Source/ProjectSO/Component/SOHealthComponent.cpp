// Fill out your copyright notice in the Description page of Project Settings.


#include "SOHealthComponent.h"

USOHealthComponent::USOHealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), Health(100.0f), MaxHealth(100.0f)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

float USOHealthComponent::GetHealth() const
{
	return Health;
}

void USOHealthComponent::SetHealth(float InHealth) 
{
	Health = InHealth;
}

float USOHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}
