// Fill out your copyright notice in the Description page of Project Settings.


#include "SOStatComponent.h"

#include "ProjectSO/ProjectSO.h"

USOStatComponent::USOStatComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), CurrentHp(100.0f), MaxHP(100.0f)
{
	// PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

float USOStatComponent::GetCurrentHp() const
{
	return CurrentHp;
}

void USOStatComponent::SetCurrentHp(float InHealth) 
{
	CurrentHp = FMath::Clamp<float>(InHealth, 0.0f, MaxHP);
	SO_SUBLOG(LogTemp, Warning, TEXT("CurrentHp %f"), CurrentHp)
	OnHPChanged.Broadcast(CurrentHp, MaxHP);
}

float USOStatComponent::GetMaxHP() const
{
	return MaxHP;
}

float USOStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0.0f, InDamage);

	SetCurrentHp(PrevHp - ActualDamage);
	
	if (CurrentHp <= KINDA_SMALL_NUMBER) 
	{
		// Hp가 다 달았을 때, 다음과 같은 함수 호출.
		if (OnHpZero.IsBound())
		{
			OnHpZero.Broadcast();
		}
	}
	
	return ActualDamage;
}
