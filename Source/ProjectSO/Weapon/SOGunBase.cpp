// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGunBase.h"
#include "Net/UnrealNetwork.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectSO/Core/SOGameSubsystem.h"

// Sets default values
ASOGunBase::ASOGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetVisibility(true, false);	
	RootComponent = WeaponMesh;
	
	CurrentFireMode = ESOFireMode::Single;
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

void ASOGunBase::PressLMB()
{
	OnFire();
}

void ASOGunBase::OnFire()
{
	switch (CurrentFireMode)
	{
	case ESOFireMode::Auto:
		AutoFire();
		break;
	case ESOFireMode::Burst:
		BurstFire();
		break;
	case ESOFireMode::Single:
		SingleFire();
		break;
	default:
		break;
	}	
}

void ASOGunBase::AutoFire()
{
	
}

void ASOGunBase::BurstFire()
{
	
}

void ASOGunBase::SingleFire()
{
}

void ASOGunBase::FireProjectile()
{
}

void ASOGunBase::CreateProjectile(FVector StartPosition, FRotator StartRotation)
{
}

void ASOGunBase::ShowEffect(FVector StartPosition, FRotator StartRotation)
{
}

void ASOGunBase::PlaySound()
{
}

void ASOGunBase::Recoil()
{
}

void ASOGunBase::Reload()
{
}

void ASOGunBase::Aim()
{
	
}

void ASOGunBase::SetGunData()
{
}


void ASOGunBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASOGunBase, OwningCharacter);
	DOREPLIFETIME(ASOGunBase, ClipSize);
	DOREPLIFETIME(ASOGunBase, MaxAmmoCapacity);
	DOREPLIFETIME(ASOGunBase, bInfiniteAmmo);
	DOREPLIFETIME(ASOGunBase, CurrentFireMode);
	DOREPLIFETIME(ASOGunBase, bReloading);
	DOREPLIFETIME(ASOGunBase, bTrigger);
	DOREPLIFETIME(ASOGunBase, CurrentAmmo);
	DOREPLIFETIME(ASOGunBase, CurrentAmmoInClip);
}

void ASOGunBase::MulticastRPCShowEffect_Implementation(FVector StartPosition, FRotator StartRotation)
{
	
}

void ASOGunBase::ServerRPCOnFire_Implementation(FVector StartPosition, FRotator StartRotation)
{
	
}

