// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "SOHUDLayout.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API USOHUDLayout : public USOUserWidget
{
	GENERATED_BODY()

public:
	USOHUDLayout(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeConstruct() override;
};
