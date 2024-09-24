// Fill out your copyright notice in the Description page of Project Settings.

#include "SOHpBarWidget.h"
#include "Components/ProgressBar.h"

USOHpBarWidget::USOHpBarWidget(const FObjectInitializer& ObjectInitializer)
{
	
}

void USOHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USOHpBarWidget::UpdateHpBar(float NewCurrentHpRatio)
{
	if(HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHpRatio);
	}
}
