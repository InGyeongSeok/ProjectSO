// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SOProjectilePoolComponent.generated.h"


class ASOProjectileBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSO_API USOProjectilePoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USOProjectilePoolComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	UFUNCTION()
	ASOProjectileBase* PullProjectile();
	
	UFUNCTION()
	void PushProjectileInPool(ASOProjectileBase* Projectile);

	void SetAmmoClass(TSubclassOf<ASOProjectileBase> InAmmoClass);

	UFUNCTION()
	void Expand();
	
	//initialize
	void Initialize();

protected:
	// Multi

public:
	UPROPERTY()
	TArray<ASOProjectileBase*> Pool;
	
protected:
	TSubclassOf<ASOProjectileBase> AmmoClass;
	
	UPROPERTY()
	int InitialPoolSize;
	
	UPROPERTY()
	int ExpandSize;
	

		
};


