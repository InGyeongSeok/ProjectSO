// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animation/ALSCharacterAnimInstance.h"
#include "SOCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API USOCharacterAnimInstance : public UALSCharacterAnimInstance
{
	GENERATED_BODY()
	USOCharacterAnimInstance();

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
