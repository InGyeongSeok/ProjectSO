// Fill out your copyright notice in the Description page of Project Settings.


#include "SOMinigun.h"

ASOMinigun::ASOMinigun()
{
}

void ASOMinigun::BeginPlay()
{
	Super::BeginPlay();
}

void ASOMinigun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASOMinigun::AutoFire()
{
	Super::AutoFire();
}

void ASOMinigun::BurstFire()
{
	Super::BurstFire();
}

void ASOMinigun::SingleFire()
{
	Super::SingleFire();
}

void ASOMinigun::FireProjectile()
{
	Super::FireProjectile();
}

void ASOMinigun::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	Super::CreateProjectile(MuzzleTransform, HitLocation);
}

void ASOMinigun::ShowEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation)
{
	Super::ShowEffect(MuzzleLocation, MuzzleRotation);
}

void ASOMinigun::PlaySound()
{
	Super::PlaySound();
}

void ASOMinigun::Recoil()
{
	Super::Recoil();
}

void ASOMinigun::PressLMB()
{
	Super::PressLMB();
}

void ASOMinigun::OnFire()
{
	Super::OnFire();
}

void ASOMinigun::Reload()
{
	Super::Reload();
}

void ASOMinigun::Aim()
{
	Super::Aim();
}
