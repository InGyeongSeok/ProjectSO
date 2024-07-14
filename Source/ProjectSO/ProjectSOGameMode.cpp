// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectSOGameMode.h"
#include "ProjectSOCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectSOGameMode::AProjectSOGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
