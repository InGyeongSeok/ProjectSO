// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectSO/Actor/SOItemActor.h"
#include "ProjectSO/Core/SOGameSubsystem.h"
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
	virtual void SetPartsData(const ESOGunPartsName InPartsName);
	virtual void SetPartsData(const FName InPartsName);
	virtual void SetPartsStat(const uint8 InID, ESOGunPartsType PartsType);
	virtual void SetPartsStat(const ESOGunPartsName InPartsName, ESOGunPartsType PartsType);
	virtual void SetPartsStat(const FName InPartsName, ESOGunPartsType PartsType);
	//Subsystem
	USOGameSubsystem* GetSOGameSubsystem();
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> PartsMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCapsuleComponent> CollisionComp;

public:
	// UPROPERTY(BlueprintReadOnly)
	// int32 ID;

	// UPROPERTY(EditInstanceOnly)
	// ESOGunPartsName PartsName;

	UPROPERTY(EditInstanceOnly)
	FName PartsName;
	
	UPROPERTY(VisibleAnywhere)
	FSOGunPartsBaseData PartsData;

	UPROPERTY(VisibleAnywhere)
	FSOPartsStat PartsStat;	
};
