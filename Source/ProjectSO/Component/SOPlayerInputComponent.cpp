// Fill out your copyright notice in the Description page of Project Settings.


#include "SOPlayerInputComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ALSDebugComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectSO/Player/SOPlayerController.h"

// Sets default values for this component's properties
USOPlayerInputComponent::USOPlayerInputComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bReadyToBindInputs = false;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultInputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/StellarObsidian/Input/IMC_SODefault.IMC_SODefault'"));
	if (DefaultInputMappingContextRef.Object)
	{
		DefaultInputMappingContext = DefaultInputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DebugInputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/StellarObsidian/Input/IMC_SODebug.IMC_SODebug'"));
	if (DebugInputMappingContextRef.Object)
	{
		DebugInputMappingContext = DebugInputMappingContextRef.Object;
	}
	
}


// Called when the game starts
void USOPlayerInputComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* OwnerActor = GetOwner();
	OwnerCharacter = Cast<ASOCharacterBase>(OwnerActor);

	// APawn* Pawn = GetPawn<APawn>();
	if (OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s 1"), *FString(__FUNCTION__))
		if (APawn* Pawn = GetPawn<APawn>())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s 2"), *FString(__FUNCTION__))
			if (ASOPlayerController* SOPC = Cast<ASOPlayerController>(Pawn->GetController()))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s 3"), *FString(__FUNCTION__))
				if (Pawn->InputComponent != nullptr)
				{
					InitializePlayerInput(Pawn->InputComponent);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Pawn's InputComponent is not initialized!"));
				}
			}
		}
		MovementState = OwnerCharacter->GetMovementState();
		AimingRotation = OwnerCharacter->GetAimingRotation();
	}
}

void USOPlayerInputComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Begin"), *FString(__FUNCTION__))
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// 캐릭터의 실질적인 로직 가져오기
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->ClearActionEventBindings();
		EnhancedInputComponent->ClearActionValueBindings();
		EnhancedInputComponent->ClearDebugKeyBindings();
		SetPlayerInputs();
		BindActions(DebugInputMappingContext);
		BindActions(DefaultInputMappingContext);
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("ALS Community requires Enhanced Input System to be activated in project settings to function properly"));
	}

	if (ensure(!bReadyToBindInputs))
	{
		bReadyToBindInputs = true;
	}
}

void USOPlayerInputComponent::BindActions(UInputMappingContext* Context)
{
	if (Context)
	{
		const TArray<FEnhancedActionKeyMapping>& Mappings = Context->GetMappings();
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwnerCharacter->InputComponent);
		if (EnhancedInputComponent)
		{
			// EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &USOPlayerInputComponent::ForwardMovementAction);
			// UE_LOG(LogTemp, Warning, TEXT("%s %s"), *FString(__FUNCTION__), *MoveAction->GetName())
			// There may be more than one keymapping assigned to one action. So, first filter duplicate action entries to prevent multiple delegate bindings
			TSet<const UInputAction*> UniqueActions;
			for (const FEnhancedActionKeyMapping& Keymapping : Mappings)
			{
				UniqueActions.Add(Keymapping.Action);
			}
			for (const UInputAction* UniqueAction : UniqueActions)
			{
				EnhancedInputComponent->BindAction(UniqueAction, ETriggerEvent::Triggered, Cast<UObject>(this), UniqueAction->GetFName());
			}
		}
	}
}

void USOPlayerInputComponent::SetPlayerInputs()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Begin"), *FString(__FUNCTION__))
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn is null!"));
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		FModifyContextOptions Options;
		Options.bForceImmediately = 1;
		Subsystem->AddMappingContext(DefaultInputMappingContext, 1, Options);
		
		UALSDebugComponent* DebugComp = Cast<UALSDebugComponent>(OwnerCharacter->GetComponentByClass(UALSDebugComponent::StaticClass()));
		if (DebugComp)
		{
			// Do only if we have debug component
			Subsystem->AddMappingContext(DebugInputMappingContext, 0, Options);
			UE_LOG(LogTemp, Warning, TEXT("%s DebugComp"), *FString(__FUNCTION__))
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputLocalPlayerSubsystem is null!"));
	}
}

bool USOPlayerInputComponent::IsReadyToBindInputs() const
{
	return bReadyToBindInputs;
}

void USOPlayerInputComponent::ForwardMovementAction(const FInputActionValue& InputValue)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Begin"), *FString(__FUNCTION__))
	
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;
	float Value = InputValue.GetMagnitude();
	
	if (MovementState == EALSMovementState::Grounded || MovementState == EALSMovementState::InAir)
	{		
		// Default camera relative movement behavior
		// AimingRotation가 아닌 컨트롤러 회전값을 가져옴
		const FRotator DirRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		Pawn->AddMovementInput(UKismetMathLibrary::GetForwardVector(DirRotator), Value);
	}
}

void USOPlayerInputComponent::RightMovementAction(const FInputActionValue& InputValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;
	float Value = InputValue.GetMagnitude();

	if (MovementState == EALSMovementState::Grounded || MovementState == EALSMovementState::InAir)
	{
		// Default camera relative movement behavior
		const FRotator DirRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		Pawn->AddMovementInput(UKismetMathLibrary::GetRightVector(DirRotator), Value);
	}
	
}

void USOPlayerInputComponent::CameraUpAction(const FInputActionValue& InputValue)
{
	APawn* Pawn = GetPawn<APawn>();
	float Value = InputValue.GetMagnitude();
	Pawn->AddControllerPitchInput(LookUpDownRate * Value);
}

void USOPlayerInputComponent::CameraRightAction(const FInputActionValue& InputValue)
{
	APawn* Pawn = GetPawn<APawn>();
	float Value = InputValue.GetMagnitude();
	Pawn->AddControllerYawInput(LookLeftRightRate * Value);
}

void USOPlayerInputComponent::JumpAction(const FInputActionValue& InputValue)
{
	uint8 bValue = InputValue.Get<bool>();
	
	/*if (bValue)
	{
		// Jump Action: Press "Jump Action" to end the ragdoll if ragdolling, stand up if crouching, or jump if standing.
		if (JumpPressedDelegate.IsBound())
		{
			JumpPressedDelegate.Broadcast();
		}

		if (MovementAction == EALSMovementAction::None)
		{
			if (MovementState == EALSMovementState::Grounded)
			{
				if (Stance == EALSStance::Standing)
				{
					Jump();
				}
				else if (Stance == EALSStance::Crouching)
				{
					UnCrouch();
				}
			}
			else if (MovementState == EALSMovementState::Ragdoll)
			{
				ReplicatedRagdollEnd();
			}
		}
	}
	else
	{
		StopJumping();
	}*/
}

void USOPlayerInputComponent::SprintAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::AimAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::CameraTapAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::CameraHeldAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::StanceAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::WalkAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::RagdollAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::VelocityDirectionAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::LookingDirectionAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugToggleHudAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugToggleDebugViewAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugToggleTracesAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugToggleShapesAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugToggleLayerColorsAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugToggleCharacterInfoAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugToggleSlowMotionAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugFocusedCharacterCycleAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugToggleMeshAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugOpenOverlayMenuAction(const FInputActionValue& InputValue)
{
}

void USOPlayerInputComponent::DebugOverlayMenuCycleAction(const FInputActionValue& InputValue)
{
}
