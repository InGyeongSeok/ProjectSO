// Fill out your copyright notice in the Description page of Project Settings.


#include "SOProjectilePoolComponent.h"

#include "Net/UnrealNetwork.h"
#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Character/SOCharacterBase.h"
#include "ProjectSO/Weapon/SOProjectileBase.h"

// Sets default values for this component's properties
USOProjectilePoolComponent::USOProjectilePoolComponent()
{
	//Todo 숫자
	InitialPoolSize = 10;
	ExpandSize = 1;
}


// Called when the game starts
void USOProjectilePoolComponent::BeginPlay()
{
	Super::BeginPlay();
	// SetIsReplicated(true);
	// Initialize();
}


void USOProjectilePoolComponent::PushProjectileInPool(ASOProjectileBase* Projectile)
{
	Pool.Push(Projectile);
}

void USOProjectilePoolComponent::SetAmmoClass(TSubclassOf<ASOProjectileBase> InAmmoClass)
{
	AmmoClass = InAmmoClass;
}

void USOProjectilePoolComponent::Expand()
{
	if (AmmoClass)
	{
		for (int i = 0; i < ExpandSize; i++)
		{
			FTransform SpawnTransform(FRotator().ZeroRotator, FVector().ZeroVector);
			ASOProjectileBase* SpawnedProjectile = GetWorld()->SpawnActorDeferred<ASOProjectileBase>(AmmoClass, SpawnTransform);
			if(SpawnedProjectile)
			{
				SpawnedProjectile->SetProjectileActive(false);
				SpawnedProjectile->ProjectilePool = this;
				SpawnedProjectile->FinishSpawning(SpawnTransform);
			}
			Pool.Push(SpawnedProjectile);
			// ASOProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<ASOProjectileBase>(AmmoClass, FVector().ZeroVector, FRotator().ZeroRotator);
			// SpawnedProjectile->SetProjectileActive(false);
			// SpawnedProjectile->ProjectilePool = this;
			// Pool.Push(SpawnedProjectile);
		}
	}
}

void USOProjectilePoolComponent::Initialize()
{
	if (AmmoClass)
	{
		for (int i = 0; i < InitialPoolSize; i++)
		{
			// ASOProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<ASOProjectileBase>(AmmoClass, FVector().ZeroVector, FRotator().ZeroRotator);
			// SpawnedProjectile->SetProjectileActive(false);
			// SpawnedProjectile->ProjectilePool = this;
			
			FTransform SpawnTransform(FRotator().ZeroRotator, FVector().ZeroVector);
			ASOProjectileBase* SpawnedProjectile = GetWorld()->SpawnActorDeferred<ASOProjectileBase>(AmmoClass, SpawnTransform);
			if(SpawnedProjectile)
			{
				
				SpawnedProjectile->SetProjectileActive(false);
				SpawnedProjectile->ProjectilePool = this;
				// ASOGunBase* GunBaseTest = Cast<ASOGunBase>(this->GetOwner());
				// SpawnedProjectile->SetOwner(GunBaseTest->GetOwner());
				// SO_SUBLOG(LogTemp, Warning, TEXT("%s"), *GunBaseTest->GetOwner()->GetName());
				SpawnedProjectile->FinishSpawning(SpawnTransform);
			}
			Pool.Push(SpawnedProjectile);
		}
	}
}


ASOProjectileBase* USOProjectilePoolComponent::PullProjectile()
{
	if (Pool.Num() <= 0)
	{
		// 실패했을 때 처리하기
		Expand();
	}
	
	SO_SUBLOG(LogTemp, Warning, TEXT("Pool Num :  %d"), Pool.Num());
	
	return Pool.Pop();
}


