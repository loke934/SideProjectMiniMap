// Copyright Epic Games, Inc. All Rights Reserved.

#include "UIMiniMapGameMode.h"
#include "UIMiniMapCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUIMiniMapGameMode::AUIMiniMapGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
