
#pragma once

#include "CoreMinimal.h"
#include "SOWeaponEnumLibrary.generated.h"

UENUM(BlueprintType)
enum class ESOWeaponType
{
	Pistol,
	AR,
	SR,
	ShotGun,
	Minigun,
};

// 발사 모드 비트 플래그 정의
UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ESOFireMode : uint8
{	
	None   = 0		UMETA(Hidden),	
	Auto   = 1 << 0,   // 1   0000 0001 
	Burst  = 1 << 1,   // 2	  0000 0010
	Single = 1 << 2,   // 4   0000 0100
	
	Max    = 1 << 7	UMETA(Hidden),   // 1000 0000
};

UENUM(BlueprintType)
enum class ESOAmmoType
{
	None,
	Ammo5_56,
	Ammo7_62,
	Ammo9,
	Ammo12,	
};