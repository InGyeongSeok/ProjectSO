// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_LOCALROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole()))
#define LOG_REMOTEROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole()))
#define LOG_SUBLOCALROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetLocalRole()))
#define LOG_SUBREMOTEROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetRemoteRole()))


#define LOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), static_cast<int32>(GPlayInEditorID)) : ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("DEDICATED")))
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
#define SO_LOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("[%s][%s/%s] %s %s"), LOG_NETMODEINFO, LOG_LOCALROLEINFO, LOG_REMOTEROLEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define SO_SUBLOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("[%s][%s/%s] %s %s"), LOG_NETMODEINFO, LOG_SUBLOCALROLEINFO, LOG_SUBREMOTEROLEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))



DECLARE_LOG_CATEGORY_EXTERN(LogSONetwork, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSOTemp, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSOProjectileBase, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSOPartsBase, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSOAI, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSOSubsystem, Log, All);


#define ECC_Item ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel2
#define ECC_ProjectileLaser ECollisionChannel::ECC_GameTraceChannel3

#define PERCENT 0.01