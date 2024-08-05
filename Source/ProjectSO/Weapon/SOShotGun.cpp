// Fill out your copyright notice in the Description page of Project Settings.


#include "SOShotGun.h"

#include "Kismet/KismetMathLibrary.h"
#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Character/SOCharacterBase.h"

ASOShotGun::ASOShotGun()
{
	Spread = 100;
	ShrapnelCount = 8;
}

void ASOShotGun::BeginPlay()
{
	Super::BeginPlay();
	// SetGunData(7);
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
	SO_LOG(LogSOTemp, Log, TEXT("ShotGun"))

	for(int i =0; i< ShrapnelCount; ++i)
	{
		// 변수로 빼기
		AController* OwnerController = OwningCharacter->GetController();
		if (OwnerController == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("OwnerController"));
			return;
		}

		// 화면 중앙 LineTrace
		FVector TraceStartLocation;
		FRotator TraceStartRotation;
		OwnerController->GetPlayerViewPoint(TraceStartLocation, TraceStartRotation);

		FVector TraceEnd = TraceStartLocation + TraceStartRotation.Vector() *  WeaponStat.MaxRange * 100 +  SpreadTraceEnd();
		FTransform MuzzleSocketTransform = GetSocketTransformByName(WeaponData.MuzzleSocketName, WeaponMesh);
		FTransform AmmoEjectSocketTransform = GetSocketTransformByName(AmmoEjectSocketName, WeaponMesh);

		DrawDebugLine(GetWorld(), MuzzleSocketTransform.GetLocation(), TraceEnd, FColor::Red,false, 5, 0, 2);

		FRotator MuzzleRotation = MuzzleSocketTransform.GetRotation().Rotator();
		FRotator EjectRotation = AmmoEjectSocketTransform.GetRotation().Rotator();

		// 효과 재생
		PlayMuzzleEffect(MuzzleSocketTransform.GetLocation(), MuzzleRotation);
		PlayEjectAmmoEffect(AmmoEjectSocketTransform.GetLocation(), EjectRotation);
		PlaySound();
		ServerRPCOnFire(MuzzleSocketTransform, TraceEnd);
	}
}

void ASOShotGun::CreateProjectile(const FTransform& MuzzleTransform, const FVector& HitLocation)
{
	Super::CreateProjectile(MuzzleTransform, HitLocation);
}

FVector ASOShotGun::SpreadTraceEnd()
{
	FVector OutTraceEnd;
	OutTraceEnd.X = UKismetMathLibrary::RandomFloatInRange(Spread * -1, Spread);
	OutTraceEnd.Y = UKismetMathLibrary::RandomFloatInRange(Spread * -1, Spread);
	OutTraceEnd.Z = UKismetMathLibrary::RandomFloatInRange(Spread * -1, Spread);

	return OutTraceEnd;
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
