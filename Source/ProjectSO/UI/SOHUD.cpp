// Fill out your copyright notice in the Description page of Project Settings.


#include "SOHUD.h"

#include "SOHUDLayout.h"
#include "Blueprint/UserWidget.h"


void ASOHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ASOHUD::AddHUDLayout(APlayerController* PC)
{
	if(PC)
	{
		HUDLayout = CreateWidget<USOHUDLayout>(PC,HUDLayoutClass);
		HUDLayout->AddToViewport();
	}
}
