
#pragma once

#include "CoreMinimal.h"
#include "SOGunPartsEnumLibrary.generated.h"

UENUM(BlueprintType)
enum class ESOGunPartsType
{
	Scope,
	MuzzleAttachment,
	Grip,
	Magazine,
	Stock,
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ESOGunPartsName : uint8
{
	RedDotSight,
	Scope4x,
	Scope8x,
	
	Compensator,
	Suppressor,
	FlashSuppressor,
	
	AngledGrip,
	VerticalGrip,
	
	Extended_556,
	Quickdraw_556,
	ExtendedQuickdraw_556,
	Extended_762,
	Quickdraw_762,
	ExtendedQuickdraw_762,
	Extended_12,
	Quickdraw_12,
	ExtendedQuickdraw_12,
	Extended_9,
	Quickdraw_9,
	ExtendedQuickdraw_9,
	MAX UMETA(Hidden)
};

/*UENUM(BlueprintType)
enum class ESOMuzzle
{
	Compensator,
	Suppressor,
	FlashSuppressor
};

UENUM(BlueprintType)
enum class ESOScope
{
	RedDotSight,
	Scope4x,
	Scope8x
};

UENUM(BlueprintType)
enum class ESOGrip
{
	AngledGrip,
	VerticalGrip
};

UENUM(BlueprintType)
enum class ESOMagazine
{
	Extended_556,
	Quickdraw_556,
	ExtendedQuickdraw_556,
	Extended_762,
	Quickdraw_762,
	ExtendedQuickdraw_762,
	Extended_12,
	Quickdraw_12,
	ExtendedQuickdraw_12,
	Extended_9,
	Quickdraw_9,
	ExtendedQuickdraw_9,
};


UENUM(BlueprintType)
enum class ESOStock
{
	TacticalStock,
	CheekPad
};*/