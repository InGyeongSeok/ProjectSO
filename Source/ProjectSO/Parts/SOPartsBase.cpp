// Fill out your copyright notice in the Description page of Project Settings.


#include "SOPartsBase.h"

#include "Components/CapsuleComponent.h"
#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Component/SOInventoryComponent.h"
#include "ProjectSO/Character/SOCharacterBase.h"

// Sets default values
ASOPartsBase::ASOPartsBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	PartsMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PartsMesh"));
	PartsMesh->SetCollisionProfileName(TEXT("PartsMesh"));
	PartsMesh->CastShadow = true;
	PartsMesh->SetVisibility(true, false);
	RootComponent = PartsMesh;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));
	CollisionComp->InitCapsuleSize(40.0f, 40.0f);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASOPartsBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASOPartsBase::OnSphereBeginOverlap);
	// CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ASOPartsBase::OnSphereEndOverlap);
}

// Called every frame
void ASOPartsBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASOPartsBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SO_LOG(LogSOPartsBase, Warning, TEXT("Begin"))
	if(HasAuthority())
	{
		ASOCharacterBase* CharacterBase = Cast<ASOCharacterBase>(OtherActor);
		if(CharacterBase)
		{
			USOInventoryComponent* Inven = CharacterBase->GetInventory();
			// 인벤토리 컴포넌트 가져오기
			Inven->AddToInventory(this);
			// CharacterBase->EquipItem(this);
		}
	}
}

void ASOPartsBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

EALSOverlayState ASOPartsBase::GetOverlayState() const
{
	return EALSOverlayState::Default;
	// return WeaponData.OverlayState;
}

void ASOPartsBase::Equip()
{
	// 무기에 장착
	
}



