// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectSO/Interface/SOInteractableInterface.h"
#include "ProjectSO/Interface/SOEquippableInterface.h"
#include "SOItemActor.generated.h"

UCLASS()
class PROJECTSO_API ASOItemActor : public AActor, public ISOEquippableInterface, public ISOInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASOItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual EALSOverlayState GetOverlayState() const override {return EALSOverlayState::Default;}
	virtual void Equip() override {};
	virtual void Interact(ASOCharacterBase* PlayerCharacter) override{};
	
};
