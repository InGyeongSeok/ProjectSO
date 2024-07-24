// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SOEquippableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USOEquippableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSO_API ISOEquippableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual EALSOverlayState GetOverlayState() const = 0;
};
