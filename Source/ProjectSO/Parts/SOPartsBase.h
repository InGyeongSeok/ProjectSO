// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectSO/Actor/SOItemActor.h"
#include "ProjectSO/Library/SOGunPartsStructLibrary.h"
#include "ProjectSO/Library/SOWeaponStructLibrary.h"
#include "SOPartsBase.generated.h"


enum class ESOGunPartsType;
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
	virtual void Interact(ASOCharacterBase* PlayerCharacter) override;
	/* ======================= Function ======================= */
public:
	void AttachToWeapon(ASOGunBase* Weapon);

protected:
	virtual void SetPartsData(const uint8 InID);
	
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> PartsMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCapsuleComponent> CollisionComp;

public:
	UPROPERTY(EditDefaultsOnly)
	int32 ID;
	
	UPROPERTY(VisibleAnywhere)
	FSOGunPartsBaseData PartsData;

	UPROPERTY(VisibleAnywhere)
	FSOPartsStat PartsStat;	
};
