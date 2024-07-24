// Fill out your copyright notice in the Description page of Project Settings.


#include "SORifle.h"

ASORifle::ASORifle()
{
}

void ASORifle::BeginPlay()
{
	Super::BeginPlay();
}

void ASORifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASORifle::PressLMB()
{
	Super::PressLMB();
}

void ASORifle::OnFire()
{
	Super::OnFire();

	
}

void ASORifle::AutoFire()
{
	Super::AutoFire();
}

void ASORifle::BurstFire()
{
	Super::BurstFire();
}

void ASORifle::SingleFire()
{
	Super::SingleFire();
}

void ASORifle::FireProjectile()
{
	Super::FireProjectile();
}

void ASORifle::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	Super::CreateProjectile(MuzzleTransform, HitLocation);
}

void ASORifle::ShowEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation)
{
	Super::ShowEffect(MuzzleLocation, MuzzleRotation);
}

void ASORifle::PlaySound()
{
	Super::PlaySound();
}

void ASORifle::Recoil()
{
	Super::Recoil();
}

void ASORifle::Reload()
{
	Super::Reload();
}

void ASORifle::Aim()
{
	Super::Aim();
}
