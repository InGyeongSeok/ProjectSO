// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOGunBase.h"
#include "SOMinigun.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSO_API ASOMinigun : public ASOGunBase
{
	GENERATED_BODY()

	/** IDamageable **/
public:
	virtual void PressLMB() override;
	
protected:
	virtual void Fire() override;
	virtual void Reload() override;
	virtual void Aim() override;
};
