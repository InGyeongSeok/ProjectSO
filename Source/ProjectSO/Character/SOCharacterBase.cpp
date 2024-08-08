// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCharacterBase.h"

#include "Character/ALSCharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "ProjectSO/ProjectSO.h"
#include "ProjectSO/Component/SOHealthComponent.h"
#include "ProjectSO/Weapon/SOGunBase.h"
#include "ProjectSO/Weapon/SOMinigun.h"

ASOCharacterBase::ASOCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HealthComponent = CreateDefaultSubobject<USOHealthComponent>(TEXT("HealthComponent"));
	
}

void ASOCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		OnTakeAnyDamage.AddDynamic(this, &ASOCharacterBase::ReceiveDamage);
	}
}

void ASOCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Cast<ASOMinigun>(CurrentWeapon))
	{
		UpdateCharacterMinigunMovement();
	}
}


void ASOCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASOCharacterBase, CurrentWeapon);
}

void ASOCharacterBase::EquipItem(ISOEquippableInterface* InEquipment)
{	
	ASOGunBase* Weapon = Cast<ASOGunBase>(InEquipment);
	
	if(Weapon)
	{
		MulticastRPCEquipItem(Weapon);		
	}
}

void ASOCharacterBase::AimAction_(bool bValue)
{
	if (bValue)
	{
		SetRotationMode(EALSRotationMode::Aiming);
		if(CurrentWeapon)
		{
			CurrentWeapon->Aim(bValue);
		}
	}
	else
	{
		if(CurrentWeapon)
		{
			CurrentWeapon->Aim(bValue);
			// 총이 확대 조준중이라면 
			if(CurrentWeapon->GetScopeAim())
			{
				SetViewMode(EALSViewMode::FirstPerson);
				SetRotationMode(EALSRotationMode::Aiming);
			}
			else
			{
				SetViewMode(EALSViewMode::ThirdPerson);
				SetRotationMode(DesiredRotationMode);
			}
				
		}
		else
		{
			if (ViewMode == EALSViewMode::ThirdPerson)
			{
				SetRotationMode(DesiredRotationMode);
			}
			else if (ViewMode == EALSViewMode::FirstPerson)
			{
				SetRotationMode(EALSRotationMode::LookingDirection);
			}
		}		
	}
}

void ASOCharacterBase::ReloadAction(bool bValue)
{
	if (bValue)
	{
		if(CurrentWeapon)
		{
			CurrentWeapon->Reload();
		}
	}
}

void ASOCharacterBase::UpdateCharacterMinigunMovement()
{
	if (MovementState == EALSMovementState::Grounded)
	{
		const EALSGait AllowedGait = EALSGait::Walking;
		const EALSGait ActualGait = EALSGait::Walking;
		if (ActualGait != Gait)
		{
			SetGait(ActualGait);
		}
		MyCharacterMovementComponent->SetAllowedGait(AllowedGait);
	}
}

void ASOCharacterBase::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                     AController* InstigatorController, AActor* DamageCauser)
{
	// 이 부분 전부 HealthComponent에서 해도 될 듯.
	float DamageToHealth = Damage;
	float Health = HealthComponent->GetHealth();
	float MaxHealth = HealthComponent->GetMaxHealth();
	Health = FMath::Clamp(Health - DamageToHealth, 0.f, MaxHealth);
	HealthComponent->SetHealth(Health);

	SO_LOG(LogTemp, Warning, TEXT("Health %f"), Health);
	// 죽음 처리 
}



void ASOCharacterBase::MulticastRPCEquipItem_Implementation(ASOGunBase* Weapon)
{
	OverlayState = Weapon->GetOverlayState();
	CurrentWeapon = Weapon;
	// CurrentWeapon->SetOwner(this);
	CurrentWeapon->SetOwningCharacter(this);
	CurrentWeapon->Equip();
}

void ASOCharacterBase::ChangeFireModeAction_Implementation(bool bValue)
{
	if (CurrentWeapon == nullptr) return;
	// 총의 발사 모드 개수 확인
	int32 AvailableModeCount = CurrentWeapon->GetAvailableFireModeCount();
	
	if (AvailableModeCount <= 1)
	{
		SO_LOG(LogSOTemp, Log, TEXT("다른 모드는 없습니다."))
		return;
	}
	if (bValue)
	{
		ESOFireMode NextFireMode = CurrentWeapon->GetNextValidFireMode();		
		CurrentWeapon->SetCurrentFireMode(NextFireMode);
		
		SO_LOG(LogSOTemp, Log, TEXT("%hhd Mode"), CurrentWeapon->GetCurrentFireMode());
	}
}

// 총 발사 눌렀을 때
void ASOCharacterBase::AttackAction_Implementation(bool bValue)  
{
	if (bValue)
	{
		if(RotationMode == EALSRotationMode::Aiming)
		{
			if(CurrentWeapon)
			{
				CurrentWeapon->PressLMB();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Punch!"), *FString(__FUNCTION__))
			}
		}
		else
		{
			if(CurrentWeapon)
			{
				// CurrentWeapon->PressLMB();				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Punch!"), *FString(__FUNCTION__))
			}
		}
	}
	else
	{
		if(CurrentWeapon)
		{
			// 들고 있는 무기에 따른 공격 로직
			CurrentWeapon->ReleaseLMB();				
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Punch!"), *FString(__FUNCTION__))
		}
	}
}



void ASOCharacterBase::ApplyRecoil(const float InYawRecoil, const float InPitchRecil)
{
	SO_LOG(LogSONetwork,Log,TEXT("ApplyRecoil %f") ,InYawRecoil );
	float RYaw = UKismetMathLibrary::RandomFloatInRange(-InYawRecoil, InYawRecoil);
	float RPitch = UKismetMathLibrary::RandomFloatInRange(-InPitchRecil,0.0f); // 총구가 위로 더 올라가는 현상을 위함 

	AddControllerYawInput(RYaw);
	AddControllerPitchInput(RPitch);
}
