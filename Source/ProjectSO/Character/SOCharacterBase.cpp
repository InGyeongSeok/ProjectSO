// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCharacterBase.h"

ASOCharacterBase::ASOCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ASOCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASOCharacterBase::EquipGun(ASOGunBase* Equipment)
{
	OverlayState = EALSOverlayState::Rifle;
	CurrentWeapon = Equipment;
	CurrentWeapon->Equip();
}

void ASOCharacterBase::AttackAction_Implementation(bool bValue)
{
	if (bValue)
	{
		if(ViewMode == EALSViewMode::ThirdPerson && RotationMode == EALSRotationMode::Aiming)
		{
			if(CurrentWeapon)
			{
				// 들고 있는 무기에 따른 공격 로직
				CurrentWeapon->PressLMB();				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Punch!"), *FString(__FUNCTION__))
			}
		}
		
	}
}