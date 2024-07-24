// Fill out your copyright notice in the Description page of Project Settings.


#include "SOShotGun.h"

ASOShotGun::ASOShotGun()
{
}

void ASOShotGun::BeginPlay()
{
	Super::BeginPlay();
}

void ASOShotGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASOShotGun::AutoFire()
{
	Super::AutoFire();
}

void ASOShotGun::BurstFire()
{
	Super::BurstFire();
}

void ASOShotGun::SingleFire()
{
	Super::SingleFire();
}

void ASOShotGun::FireProjectile()
{
	Super::FireProjectile();
}

void ASOShotGun::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	Super::CreateProjectile(MuzzleTransform, HitLocation);
}

void ASOShotGun::ShowEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation)
{
	Super::ShowEffect(MuzzleLocation, MuzzleRotation);
}

void ASOShotGun::PlaySound()
{
	Super::PlaySound();
}

void ASOShotGun::Recoil()
{
	Super::Recoil();
}

void ASOShotGun::PressLMB()
{
	Super::PressLMB();
}

void ASOShotGun::OnFire()
{
	Super::OnFire();
}

void ASOShotGun::Reload()
{
	Super::Reload();
}

void ASOShotGun::Aim()
{
	Super::Aim();
}
