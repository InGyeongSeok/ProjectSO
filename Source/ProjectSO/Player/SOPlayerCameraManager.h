// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "SOPlayerCameraManager.generated.h"

// forward declarations
class UALSDebugComponent;
class AALSBaseCharacter;
class ASOCharacterBase;

/**
 * Player camera manager class
 */
UCLASS()
class PROJECTSO_API ASOPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ASOPlayerCameraManager();

	UFUNCTION(BlueprintCallable, Category = "ProjectSO|Camera")
	void OnPossess(AALSBaseCharacter* NewCharacter);

	UFUNCTION(BlueprintCallable, Category = "ProjectSO|Camera")
	float GetCameraBehaviorParam(FName CurveName) const;

	/** Implemented debug logic in BP */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ProjectSO|Camera")
	void DrawDebugTargets(FVector PivotTargetLocation);

protected:
	virtual void UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ProjectSO|Camera")
	static FVector CalculateAxisIndependentLag(
		FVector CurrentLocation, FVector TargetLocation, FRotator CameraRotation, FVector LagSpeeds, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "ProjectSO|Camera")
	bool CustomCameraBehavior(float DeltaTime, FVector& Location, FRotator& Rotation, float& FOV);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProjectSO|Camera")
	TObjectPtr<AALSBaseCharacter> ControlledCharacter = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProjectSO|Camera")
	TObjectPtr<USkeletalMeshComponent> CameraBehavior = nullptr;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectSO|Camera")
	FVector RootLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectSO|Camera")
	FTransform SmoothedPivotTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectSO|Camera")
	FVector PivotLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectSO|Camera")
	FVector TargetCameraLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectSO|Camera")
	FRotator TargetCameraRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProjectSO|Camera")
	FRotator DebugViewRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ProjectSO|Camera")
	FVector DebugViewOffset;

private:
	UPROPERTY()
	TObjectPtr<UALSDebugComponent> ALSDebugComponent = nullptr;
};
