// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "ProjectSO/Character/SOCharacterBase.h"
#include "SOPlayerInputComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSO_API USOPlayerInputComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USOPlayerInputComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	virtual void BindActions(UInputMappingContext* Context);  // BindAction. 함수 등록
	void SetPlayerInputs();          // AddMappingContext. IMC 추가

	/** True if this is controlled by a real player and has progressed far enough in initialization where additional input bindings can be added */
	bool IsReadyToBindInputs() const;
	
	UFUNCTION()
	void ForwardMovementAction(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void RightMovementAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void CameraUpAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void CameraRightAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void JumpAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void SprintAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void AimAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void CameraTapAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void CameraHeldAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void StanceAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void WalkAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void RagdollAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void VelocityDirectionAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void LookingDirectionAction(const FInputActionValue& InputValue);

	// Debug actions
	UFUNCTION()
	void DebugToggleHudAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugToggleDebugViewAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugToggleTracesAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugToggleShapesAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugToggleLayerColorsAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugToggleCharacterInfoAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugToggleSlowMotionAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugFocusedCharacterCycleAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugToggleMeshAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugOpenOverlayMenuAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void DebugOverlayMenuCycleAction(const FInputActionValue& InputValue);
	// ...
	
public:
	/** Main character reference */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ASOCharacterBase> OwnerCharacter = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> DefaultInputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> DebugInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(BlueprintReadOnly, Category = "State Values")
	EALSMovementState MovementState = EALSMovementState::None;

	/* Smooth out aiming by interping control rotation*/
	FRotator AimingRotation = FRotator::ZeroRotator;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly)
	float LookUpDownRate = 1.25f;

	UPROPERTY(EditDefaultsOnly, Category = "Input", BlueprintReadOnly)
	float LookLeftRightRate = 1.25f;
	
	/** True when player input bindings have been applied, will never be true for non - players */
	bool bReadyToBindInputs;

};
