// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SOReticleWidgetBase.generated.h"

/*USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()
public:
	UTexture2D* CrosshairsCenter;
	UTexture2D* CrosshairsLeft;
	UTexture2D* CrosshairsRight;
	UTexture2D* CrosshairsTop;
	UTexture2D* CrosshairsBottom;
	float CrosshairSpread;
	FLinearColor CrosshairsColor;
};*/

/**
 * 
 */
UCLASS()
class PROJECTSO_API USOReticleWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	USOReticleWidgetBase(const FObjectInitializer& ObjectInitializer);
	
private:
	UPROPERTY()
	class APlayerController* OwningPlayer;
	
public:
	// FHUDPackage HUDPackage;

	/*UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTexture2D> CrosshairsCenter;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTexture2D> CrosshairsLeft;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTexture2D> CrosshairsRight;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTexture2D> CrosshairsTop;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTexture2D> CrosshairsBottom;	*/
};
