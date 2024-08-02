// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Containers/Array.h"
#include "HAL/Platform.h"
#include "Styling/SlateBrush.h"
#include "Templates/SharedPointer.h"
#include "UObject/UObjectGlobals.h"
#include "SOCircumferenceMarkerWidget.generated.h"

class SWidget;
class UObject;
struct FFrame;

/**
 * 
 */
UCLASS()
class PROJECTSO_API USOCircumferenceMarkerWidget : public UWidget
{
	GENERATED_BODY()

public:
	USOCircumferenceMarkerWidget(const FObjectInitializer& ObjectInitializer);

	//~UWidget interface
public:
	virtual void SynchronizeProperties() override;
	
public:
	/** The list of positions/orientations to draw the markers at. */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	// TArray<FCircumferenceMarkerEntry> MarkerList;

	/** The radius of the circle. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance, meta=(ClampMin=0.0))
	float Radius = 48.0f;

	/** The marker image to place around the circle. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)
	FSlateBrush MarkerImage;
};
