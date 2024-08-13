// Fill out your copyright notice in the Description page of Project Settings.


#include "SOProjectilePoolComponent.h"
#include "ProjectSO/Weapon/SOProjectileBase.h"

// Sets default values for this component's properties
USOProjectilePoolComponent::USOProjectilePoolComponent()
{
	//Todo 숫자
	// InitialPoolSize = 10;
	ExpandSize = 1;
}


// Called when the game starts
void USOProjectilePoolComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USOProjectilePoolComponent::Reserve(int32 Count)
{
	if (AmmoClass)
	{
		for (int i = 0; i < Count; i++)
		{
			Pool.Push(CreateProjectile());
		}
	}
}


void USOProjectilePoolComponent::ReturnToPool(ASOProjectileBase* Projectile)
{
	Pool.Push(Projectile);
}

void USOProjectilePoolComponent::SetAmmoClass(TSubclassOf<ASOProjectileBase> InAmmoClass)
{
	AmmoClass = InAmmoClass;
}

ASOProjectileBase* USOProjectilePoolComponent::GetProjectile()
{
	return GetNewOrRecycle();
}


ASOProjectileBase* USOProjectilePoolComponent::CreateProjectile()
{
	if (AmmoClass)
	{
		FTransform SpawnTransform(FRotator().ZeroRotator, FVector().ZeroVector);
		ASOProjectileBase* SpawnedProjectile = GetWorld()->SpawnActorDeferred<ASOProjectileBase>(
			AmmoClass, SpawnTransform);
		if (SpawnedProjectile)
		{
			SpawnedProjectile->SetProjectileActive(false);
			SpawnedProjectile->ProjectilePool = this;
			SpawnedProjectile->FinishSpawning(SpawnTransform);
			return SpawnedProjectile;
		}
	}
	return nullptr; 
}


ASOProjectileBase* USOProjectilePoolComponent::GetNewOrRecycle()
{
	// 풀에 객체가 없을 경우
	if (Pool.Num() <= 0)
	{
		ASOProjectileBase* NewProjectile = CreateProjectile();
		if (IsValid(NewProjectile))
		{
			return NewProjectile; 
		}
		else
		{
			// 실패했을 때 처리 
			return nullptr;
		}
	}
	// 풀에 객체가 있을 경우, 풀에서 하나 꺼내서 반환
	UE_LOG(LogTemp, Warning, TEXT("Pool Num :  %d"), Pool.Num());
	ASOProjectileBase* NewProjectile = Pool.Pop();
	// NewProjectile->SetProjectileActive(true);
	return NewProjectile;
}

