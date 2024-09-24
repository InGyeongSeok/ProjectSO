// Fill out your copyright notice in the Description page of Project Settings.


#include "SOHUD.h"

#include "SOHpBarWidget.h"
#include "SOHUDLayout.h"
#include "Blueprint/UserWidget.h"
#include "ProjectSO/Interface/SOCharacterWidgetInterface.h"


void ASOHUD::BeginPlay()
{
	Super::BeginPlay();

	// Binding Delegate
	// 캐릭터에서 StatComponent의 델리게이트에 함수 바인딩 설정
	ISOCharacterWidgetInterface* CharacterHUD = Cast<ISOCharacterWidgetInterface>(PlayerOwner->GetPawn());		
	CharacterHUD->SetUpHUD(this);
}

void ASOHUD::DrawHUD()
{
	Super::DrawHUD();
	// UE_LOG(LogTemp, Log, TEXT("ASOHUD::DrawHUD()"))
}

void ASOHUD::AddHUDLayout(APlayerController* PC)
{
	if(PC)
	{
		HUDLayout = CreateWidget<USOHUDLayout>(PC,HUDLayoutClass);
		HUDLayout->AddToViewport();

		// Create HpBarWidget
		// HpBarWidget = CreateWidget<USOHpBarWidget>(PC, HpBarWidgetClass, TEXT("HpBarWidget"));
		// HpBarWidget->AddToViewport();
	}
}

void ASOHUD::UpdateHpBarWidget(float CurrentHp, float MaxHp)
{
	const float NewPercent = FMath::Clamp((CurrentHp/MaxHp),0.0f, 1.0f);
	if(HpBarWidget)
	{
		HpBarWidget->UpdateHpBar(NewPercent);		
	}
}
