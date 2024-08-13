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
	void Reserve(int32 Count = 10);
	
	UFUNCTION()
	void ReturnToPool(ASOProjectileBase* Projectile);
	
	UFUNCTION()
	void SetAmmoClass(TSubclassOf<ASOProjectileBase> InAmmoClass);

	UFUNCTION()
	ASOProjectileBase* GetProjectile();
	
protected:
	UFUNCTION()
	ASOProjectileBase* CreateProjectile();
	
	UFUNCTION()
	ASOProjectileBase* GetNewOrRecycle();

public:
	UPROPERTY()
	TArray<ASOProjectileBase*> Pool;
	
protected:
	TSubclassOf<ASOProjectileBase> AmmoClass;
	
	// UPROPERTY(EditDefaultsOnly)
	// int32 InitialPoolSize;
	
	UPROPERTY()
	int32 ExpandSize;

};


