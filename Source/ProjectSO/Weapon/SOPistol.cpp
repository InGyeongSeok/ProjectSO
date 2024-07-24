// Fill out your copyright notice in the Description page of Project Settings.


#include "SOPistol.h"

ASOPistol::ASOPistol()
{
}

void ASOPistol::BeginPlay()
{
	Super::BeginPlay();
}

void ASOPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASOPistol::AutoFire()
{
	Super::AutoFire();
}

void ASOPistol::BurstFire()
{
	Super::BurstFire();
}

void ASOPistol::SingleFire()
{
	Super::SingleFire();
}

void ASOPistol::FireProjectile()
{
	Super::FireProjectile();
}

void ASOPistol::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	Super::CreateProjectile(MuzzleTransform, HitLocation);
}

void ASOPistol::ShowEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation)
{
	Super::ShowEffect(MuzzleLocation, MuzzleRotation);
}


void ASOPistol::PlaySound()
{
	Super::PlaySound();
}

void ASOPistol::Recoil()
{
	Super::Recoil();
}

void ASOPistol::PressLMB()
{
	Super::PressLMB();
}

void ASOPistol::OnFire()
{
	Super::OnFire();
}

void ASOPistol::Reload()
{
	Super::Reload();
}

void ASOPistol::Aim()
{
	Super::Aim();
}
