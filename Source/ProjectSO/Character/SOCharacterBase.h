// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSCharacter.h"
#include "ProjectSO/Weapon/SOGunBase.h"
#include "ProjectSO/Interface/SOEquippableInterface.h"
#include "SOCharacterBase.generated.h"

class USOHealthComponent;
/**
 * 
 */
UCLASS()
class PROJECTSO_API ASOCharacterBase : public AALSCharacter
{
	GENERATED_BODY()

public:
	ASOCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// 나중에 장착 가능한 것들만 모아서 하기
	void EquipItem(ISOEquippableInterface* InEquipment);

	/** Input */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SO|Input")
	void AttackAction(bool bValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SO|Input")
	void ChangeFireModeAction(bool bValue);

	UFUNCTION(BlueprintCallable, Category = "SO|Input")
	void AimAction_(bool bValue);

	UFUNCTION(BlueprintCallable, Category = "SO|Input")
	void ReloadAction(bool bValue);
	
	
public:
	
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCEquipItem(ASOGunBase* Weapon);
	
		
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "SO|Equip")
	TObjectPtr<ASOGunBase> CurrentWeapon;


	// Health
public:
	// Blaster
	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);
	
private:
	UPROPERTY(EditAnywhere, Replicated, Category = "SO|Health")
	TObjectPtr<USOHealthComponent> HealthComponent;
};
