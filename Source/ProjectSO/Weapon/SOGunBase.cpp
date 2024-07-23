// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGunBase.h"
#include "Net/UnrealNetwork.h"

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

