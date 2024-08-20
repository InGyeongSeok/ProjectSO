// Fill out your copyright notice in the Description page of Project Settings.


#include "SOInventoryComponent.h"

#include "ProjectSO/Actor/SOItemActor.h"
#include "ProjectSO/Character/SOCharacterBase.h"

// Sets default values for this component's properties
USOInventoryComponent::USOInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USOInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USOInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USOInventoryComponent::PickupItem()
{
	
}

void USOInventoryComponent::AddToInventory(ASOItemActor* InItem)
{
	// ClientRPCAddToInventory 호출 예정
	// 원래는 인벤토리에 저장되는 기능이 있을 예정
	// InItem->SetOwner();

	// 
	AActor* OwningActor = GetOwner();
	ASOCharacterBase* SOCharacter = Cast<ASOCharacterBase>(OwningActor);
	SOCharacter->EquipItem(InItem);	
	// InItem->Equip();
}

