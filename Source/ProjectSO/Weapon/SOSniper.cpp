// Fill out your copyright notice in the Description page of Project Settings.


#include "SOSniper.h"

ASOSniper::ASOSniper()
{
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

void ASOSniper::OnFire(ESOFireMode InFireMode)
{
	Super::OnFire(InFireMode);
}

void ASOSniper::Reload()
{
	Super::Reload();
}

void ASOSniper::Aim()
{
	Super::Aim();
}
