// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectSO/Interface/SODamageableInterface.h"
#include "SOGunBase.generated.h"

UCLASS()
class PROJECTSO_API ASOGunBase : public AActor, public ISODamageableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASOGunBase();

/** IDamageable **/
public:
	virtual void PressLMB() override;

protected:
	virtual void Fire();
	virtual void Reload();
	virtual void Aim();

	void SetGunData(const uint8 InID);

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
