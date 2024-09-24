// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SOHUD.generated.h"

class USOHpBarWidget;
class USOHUDLayout;
/**
 * 
 */
UCLASS()
class PROJECTSO_API ASOHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
public:
	UFUNCTION()
	void AddHUDLayout(APlayerController* PC);	

	// 바인딩될 함수들
public:
	void UpdateHpBarWidget(float CurrentHp, float MaxHp);
	
public:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUserWidget> HUDLayoutClass;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUserWidget> HpBarWidgetClass;
	
	UPROPERTY()
	TObjectPtr<USOHUDLayout> HUDLayout;

	UPROPERTY()
	TObjectPtr<USOHpBarWidget> HpBarWidget;
};
