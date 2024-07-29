// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCharacterBase.h"

#include "ProjectSO/ProjectSO.h"

ASOCharacterBase::ASOCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ASOCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASOCharacterBase::EquipItem(ISOEquippableInterface* InEquipment)
{
	OverlayState = InEquipment->GetOverlayState();
	ASOGunBase* Weapon = Cast<ASOGunBase>(InEquipment);
	 CurrentWeapon = Weapon;
	 CurrentWeapon->Equip();
}

void ASOCharacterBase::ChangeFireModeAction_Implementation(bool bValue)
{
	if (CurrentWeapon == nullptr) return;
	// 총의 발사 모드 개수 확인
	int32 AvailableModeCount = CurrentWeapon->GetAvailableFireModeCount();
	
	if (AvailableModeCount <= 1)
	{
		SO_LOG(LogSOTemp, Log, TEXT("다른 모드는 없습니다."))
		return;
	}
	if (bValue)
	{
		ESOFireMode NextFireMode = CurrentWeapon->GetNextValidFireMode();		
		CurrentWeapon->SetCurrentFireMode(NextFireMode);
		
		SO_LOG(LogSOTemp, Log, TEXT("%hhd Mode"), CurrentWeapon->GetCurrentFireMode());
	}
}

void ASOCharacterBase::AttackAction_Implementation(bool bValue)
{
	if (bValue)
	{
		if(RotationMode == EALSRotationMode::Aiming)
		{
			if(CurrentWeapon)
			{
				CurrentWeapon->PressLMB();				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Punch!"), *FString(__FUNCTION__))
			}
		}
		else
		{
			if(CurrentWeapon)
			{
				// CurrentWeapon->PressLMB();				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Punch!"), *FString(__FUNCTION__))
			}
		}
	}
	else
	{
		if(CurrentWeapon)
		{
			// 들고 있는 무기에 따른 공격 로직
			CurrentWeapon->ReleaseLMB();				
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Punch!"), *FString(__FUNCTION__))
		}
	}
}
