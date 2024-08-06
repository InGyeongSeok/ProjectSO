// Fill out your copyright notice in the Description page of Project Settings.


#include "SOSniper.h"

#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "ProjectSO/Character/SOCharacterBase.h"
#include "ProjectSO/Player/SOPlayerController.h"

class ASOPlayerController;

ASOSniper::ASOSniper()
{
	ScopeCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ScopeCamera"));
	ScopeCamera->SetupAttachment(WeaponMesh);	
	ScopeCamera->bUsePawnControlRotation = true;

	CaptureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureCamera"));
	CaptureCamera->SetupAttachment(WeaponMesh);	
	
	Lens = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lens"));
	Lens->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Lens->SetupAttachment(WeaponMesh);
	Lens->CastShadow = true;
	Lens->SetVisibility(false);

	PressedTime = 0;
	ReleasedTime = 0;
	HoldThreshold = 0.5f;
	bScopeAim = false;
}

void ASOSniper::BeginPlay()
{
	Super::BeginPlay();
}

void ASOSniper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASOSniper::FireAuto()
{
	Super::FireAuto();
}

void ASOSniper::FireBurst(uint32 InMaxRepeatCount)
{
	Super::FireBurst(InMaxRepeatCount);
}

void ASOSniper::FireSingle()
{
	Super::FireSingle();
}

void ASOSniper::FireProjectile()
{
	Super::FireProjectile();
}

void ASOSniper::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	Super::CreateProjectile(MuzzleTransform, HitLocation);
}

void ASOSniper::PlayMuzzleEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation)
{
	Super::PlayMuzzleEffect(MuzzleLocation, MuzzleRotation);
}

void ASOSniper::PlaySound()
{
	Super::PlaySound();
}

void ASOSniper::Recoil()
{
	Super::Recoil();
}

void ASOSniper::PressLMB()
{
	Super::PressLMB();
}

void ASOSniper::Equip()
{
	Super::Equip();
	Lens->SetVisibility(false);
	
}

void ASOSniper::OnFire(ESOFireMode InFireMode)
{
	Super::OnFire(InFireMode);
}

void ASOSniper::Reload()
{
	Super::Reload();
	
}

void ASOSniper::Aim(bool bPressed)
{
	// Super::Aim(bPressed);

	if(bPressed)
	{
		PressedTime = GetWorld()->GetTimeSeconds();
		// 꾹 누르고 있는 경우엔 그냥 조준 모션만 취하기
		// 확대 조준 상태에서 다시 누르면 해제		
	}
	else
	{
		if(bScopeAim)
		{
			bScopeAim = false;
			Lens->SetVisibility(false);
			if(ASOPlayerController* PlayerController = CastChecked<ASOPlayerController>(OwningCharacter->GetController()))
			{
				PlayerController->SetViewTargetWithBlend(OwningCharacter,0.2);	
			}
			return;
		}
		ReleasedTime = GetWorld()->GetTimeSeconds();
		const float ClickDuration = ReleasedTime - PressedTime;
		if(ClickDuration < HoldThreshold)
		{
			bScopeAim = true;
			// Short click action
			Lens->SetVisibility(true);
			if(ASOPlayerController* PlayerController = CastChecked<ASOPlayerController>(OwningCharacter->GetController()))
			{
				PlayerController->SetViewTargetWithBlend(this,0.2);	
			}
		}
	}
	
}
