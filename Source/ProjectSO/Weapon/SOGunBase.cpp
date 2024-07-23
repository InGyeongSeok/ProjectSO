// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGunBase.h"

// Sets default values
ASOGunBase::ASOGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASOGunBase::PressLMB()
{
	Fire();
}

void ASOGunBase::Fire()
{
	
}

void ASOGunBase::Reload()
{
}

void ASOGunBase::Aim()
{
}

// Called when the game starts or when spawned
void ASOGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASOGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

