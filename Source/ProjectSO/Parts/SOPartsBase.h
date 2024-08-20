// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectSO/Actor/SOItemActor.h"
#include "SOPartsBase.generated.h"

class ASOGunBase;

UCLASS()
class PROJECTSO_API ASOPartsBase : public ASOItemActor
{
	GENERATED_BODY()
	
public:	
	ASOPartsBase();

	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* ======================= Interface ======================= */
public:
	virtual EALSOverlayState GetOverlayState() const override;
	virtual void Equip() override;

	/* ======================= Function ======================= */
public:
	void AttachToWeapon(ASOGunBase* Weapon);
	
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> PartsMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCapsuleComponent> CollisionComp;


	
};
