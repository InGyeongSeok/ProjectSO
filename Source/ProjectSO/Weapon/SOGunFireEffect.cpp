// Fill out your copyright notice in the Description page of Project Settings.


#include "SOGunFireEffect.h"

#include "NiagaraFunctionLibrary.h"
#include "KisMet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "ProjectSO/ProjectSO.h"

// Sets default values
ASOGunFireEffect::ASOGunFireEffect()
{
	bReplicates = true;
}

// Called when the game starts or when spawned
void ASOGunFireEffect::BeginPlay()
{
	Super::BeginPlay();
}

void ASOGunFireEffect::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ASOGunFireEffect::PlayEffect(const FTransform& MuzzleTransform, const FTransform& EjectTransform)
{
	PlayMuzzleEffect(MuzzleTransform);
	PlayEjectAmmoEffect(EjectTransform);	
}

void ASOGunFireEffect::PlayMuzzleEffect(const FTransform& MuzzleTransform)
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			MuzzleFlash,
			MuzzleTransform
		);
	}
}

void ASOGunFireEffect::PlayEjectAmmoEffect(const FTransform& EjectTransform)
{
	if(EjectShellParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), EjectShellParticles,
			EjectTransform.GetLocation(),
			EjectTransform.GetRotation().Rotator());		
	}
}

