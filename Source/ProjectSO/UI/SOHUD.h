// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SOHUD.generated.h"

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

public:
	UFUNCTION()
	void AddHUDLayout(APlayerController* PC);	
	
public:
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<class UUserWidget> HUDLayoutClass;
	
	UPROPERTY()
	TObjectPtr<USOHUDLayout> HUDLayout;
};
