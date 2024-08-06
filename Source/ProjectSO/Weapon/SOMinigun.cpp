// Fill out your copyright notice in the Description page of Project Settings.


#include "SOMinigun.h"

#include "Engine/SkeletalMeshSocket.h"
#include "KisMet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Character/SOCharacterBase.h"
#include "ProjectSO/Library/SOWeaponMeshDataAsset.h"

ASOMinigun::ASOMinigun()
{
	UE_LOG(LogTemp,Log,TEXT("ASOMinigun"));
	CanoMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("CanoMesh"));
	CanoMesh->SetCollisionProfileName(TEXT("WeaponMesh"));
	//WeaponMesh->SetCollisionEnabled();
	CanoMesh->CastShadow = true;
	CanoMesh->SetVisibility(true, false);
	CanoMesh->SetMobility(EComponentMobility::Movable);
	//CanoMesh->SetSimulatePhysics(true);
	CanoMesh->SetupAttachment(RootComponent);

	bActivateMiniGun=false;
}

void ASOMinigun::BeginPlay()
{
	UE_LOG(LogTemp,Log,TEXT("ASOMinigun : BeginPlay"));

	Super::BeginPlay();
	SetGunData(ID);
}

void ASOMinigun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASOMinigun, bActivateMiniGun);
}

void ASOMinigun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASOMinigun::FireAuto()
{
	Super::FireAuto();
}

void ASOMinigun::FireBurst(uint32 InMaxRepeatCount)
{
	Super::FireBurst(InMaxRepeatCount);
}

void ASOMinigun::FireSingle()
{
	Super::FireSingle();
}


void ASOMinigun::FireProjectile()
{
	
	AController* OwnerController = OwningCharacter->GetController();
	if (OwnerController == nullptr)
	{
		return;
	}

	// 화면 중앙 LineTrace
	FVector TraceStartLocation;
	FRotator TraceStartRotation;
	OwnerController->GetPlayerViewPoint(TraceStartLocation, TraceStartRotation);

	// 수정 필요 
	FVector TraceEnd = TraceStartLocation + TraceStartRotation.Vector() * WeaponStat.MaxRange * 100;

	FTransform MuzzleSocketTransform = GetSocketTransformByName(WeaponData.MuzzleSocketName, CanoMesh);
	FTransform AmmoEjectSocketTransform = GetSocketTransformByName(AmmoEjectSocketName, WeaponMesh);
	
	
	const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(AmmoEjectSocketName);
	const USkeletalMeshSocket* MuzzleSocket = CanoMesh->GetSocketByName(WeaponData.MuzzleSocketName);

	// ensure(AmmoEjectSocket);
	if (IsValid(AmmoEjectSocket))
	{
		AmmoEjectSocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);
	}

	if (IsValid(MuzzleSocket))
	{
		MuzzleSocketTransform = MuzzleSocket->GetSocketTransform(CanoMesh);
	}

	DrawDebugLine(GetWorld(), MuzzleSocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 5, 0, 2);

	//FRotator MuzzleRotation = MuzzleSocketTransform.GetRotation().Rotator();

	FRotator EjectRotation = AmmoEjectSocketTransform.GetRotation().Rotator();
	
	PlayMuzzleEffect(AmmoEjectSocketTransform.GetLocation(), EjectRotation);
	PlayEjectAmmoEffect(AmmoEjectSocketTransform.GetLocation(), EjectRotation);

	PlaySound();
	// bPlayFireEffect = true;
	// 총알 생성
	ServerRPCOnFire(MuzzleSocketTransform, TraceEnd);
	
}

void ASOMinigun::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	Super::CreateProjectile(MuzzleTransform, HitLocation);
}



void ASOMinigun::PlayMuzzleEffect(const FVector& MuzzleLocation, FRotator& MuzzleRotation)
{
	//Super::PlayMuzzleEffect(MuzzleLocation, MuzzleRotation);

	if (WeaponData.MuzzleFlashEffect)
	{
		FVector MuzzleFlashScale = FVector(0.3f, 0.3f, 0.3f);
		
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			WeaponData.MuzzleFlashEffect,
			MuzzleLocation,
			MuzzleRotation,
			MuzzleFlashScale
		);
	}
}

void ASOMinigun::PlaySound()
{
	Super::PlaySound();
}

void ASOMinigun::Recoil()
{
	Super::Recoil();
}

void ASOMinigun::SetGunData(const uint8 InID)
{
	Super::SetGunData(InID);
	SO_LOG(LogTemp,Log,TEXT("ASOMinigun : SetGunData"));

	if(WeaponData.WeaponMeshDataAsset)
	{
		CanoMesh->SetSkeletalMesh(WeaponData.WeaponMeshDataAsset -> WeaponSkeletalMesh[1]);
		CanoMesh->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("CanoSocket"));
	}
}

void ASOMinigun::PressLMB()
{
	Super::PressLMB();
}

void ASOMinigun::Equip() 
{
	Super::Equip();
}

void ASOMinigun::OnFire(ESOFireMode InFireMode)
{
	Super::OnFire(InFireMode);
	SO_LOG(LogSONetwork,Log,TEXT("OnFire"));
	ServerRPCActiveMiniGun();

}

void ASOMinigun::Reload()
{
	Super::Reload();
}

void ASOMinigun::Aim(bool bPressed)
{
	Super::Aim(bPressed);
}

void ASOMinigun::ServerRPCActiveMiniGun_Implementation()
{
	SO_LOG(LogSONetwork,Log,TEXT("ServerRPC"));

	bActivateMiniGun =true;
}
