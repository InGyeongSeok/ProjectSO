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

void ASOShotGun::FireAuto()
{
	Super::FireAuto();
}

void ASOShotGun::FireBurst(uint32 InMaxRepeatCount)
{
	Super::FireBurst(InMaxRepeatCount);
}

void ASOShotGun::FireSingle()
{
	Super::FireSingle();
}

void ASOShotGun::FireProjectile()
{
	Super::FireProjectile();
}

void ASOShotGun::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	Super::CreateProjectile(MuzzleTransform, HitLocation);
}

void ASOShotGun::PlayMuzzleEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation)
{
	Super::PlayMuzzleEffect(MuzzleLocation, MuzzleRotation);
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

void ASOShotGun::OnFire(ESOFireMode InFireMode)
{
	Super::OnFire(InFireMode);
}

void ASOShotGun::Reload()
{
	Super::Reload();
}

void ASOShotGun::Aim()
{
	Super::Aim();
}
