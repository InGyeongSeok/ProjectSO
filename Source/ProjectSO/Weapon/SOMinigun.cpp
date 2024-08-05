// Fill out your copyright notice in the Description page of Project Settings.


#include "SOMinigun.h"

#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Library/SOWeaponMeshDataAsset.h"

ASOMinigun::ASOMinigun()
{
	UE_LOG(LogTemp,Log,TEXT("ASOMinigun"));
	CanoMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("CanoMesh"));
	CanoMesh->SetCollisionProfileName(TEXT("WeaponMesh"));
	//WeaponMesh->SetCollisionEnabled();
	CanoMesh->CastShadow = true;
	CanoMesh->SetVisibility(true, false);
	//CanoMesh->SetMobility(EComponentMobility::Movable);
	//CanoMesh->SetSimulatePhysics(true);
	CanoMesh->SetupAttachment(RootComponent);
}

void ASOMinigun::BeginPlay()
{
	UE_LOG(LogTemp,Log,TEXT("ASOMinigun : BeginPlay"));

	Super::BeginPlay();
	SetGunData(ID);
	
}

void ASOMinigun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASOMinigun::FireAuto()
{
	Super::FireAuto();
}

void ASOMinigun::FireBurst(uint32 InMaxRepeatCount)
{
	Super::FireBurst(InMaxRepeatCount);
}

void ASOMinigun::FireSingle()
{
	Super::FireSingle();
}

void ASOMinigun::FireProjectile()
{
	Super::FireProjectile();
}

void ASOMinigun::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	Super::CreateProjectile(MuzzleTransform, HitLocation);
}

void ASOMinigun::PlayMuzzleEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation)
{
	Super::PlayMuzzleEffect(MuzzleLocation, MuzzleRotation);
}

void ASOMinigun::PlaySound()
{
	Super::PlaySound();
}

void ASOMinigun::Recoil()
{
	Super::Recoil();
}

void ASOMinigun::SetGunData(const uint8 InID)
{
	Super::SetGunData(InID);
	SO_LOG(LogTemp,Log,TEXT("ASOMinigun : SetGunData"));

	if(WeaponData.WeaponMeshDataAsset)
	{
		CanoMesh->SetSkeletalMesh(WeaponData.WeaponMeshDataAsset -> WeaponSkeletalMesh[1]);
		CanoMesh->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Cano"));
	}
}

void ASOMinigun::PressLMB()
{
	Super::PressLMB();
}

void ASOMinigun::OnFire(ESOFireMode InFireMode)
{
	Super::OnFire(InFireMode);
}

void ASOMinigun::Reload()
{
	Super::Reload();
}

void ASOMinigun::Aim()
{
	Super::Aim();
}
