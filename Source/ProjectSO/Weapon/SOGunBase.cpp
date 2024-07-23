// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGunBase.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectSO/Core/SOGameSubsystem.h"

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

void ASOGunBase::SetGunData(const uint8 InID)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is not available."));
		return;
	}

	// 게임 인스턴스를 가져옵니다.
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is not available."));
		return;
	}

	// 게임 인스턴스에서 서브시스템을 가져옵니다.
	USOGameSubsystem* SOGameSubsystem = GameInstance->GetSubsystem<USOGameSubsystem>();
	if (!SOGameSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("SOGameSubsystem is not available."));
		return;
	}

	// 서브시스템에서 WeaponStatData를 가져옵니다.
	FSOWeaponStat* WeaponStat = SOGameSubsystem->GetWeaponStatData(InID);
	if(WeaponStat)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponStat is available."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponStat is not available."));
	}
}

// Called when the game starts or when spawned
void ASOGunBase::BeginPlay()
{
	Super::BeginPlay();
	SetGunData(0);
	
}

// Called every frame
void ASOGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

