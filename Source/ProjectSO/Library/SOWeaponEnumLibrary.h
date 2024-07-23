
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
UENUM(BlueprintType)
enum class ESOFireMode : uint8
{
	None   = 0,        // 0000
	Auto   = 1 << 0, // 0001
	Burst  = 1 << 1, // 0010
	Single = 1 << 2  // 0100
};