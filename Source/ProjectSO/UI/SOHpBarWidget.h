// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOUserWidget.h"
#include "SOHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API USOHpBarWidget : public USOUserWidget
{
	GENERATED_BODY()

public:
	USOHpBarWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpProgressBar;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateHpBar(float NewCurrentHpRatio);
};
