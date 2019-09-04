// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FollowInstructionsGameMode.h"
#include "FollowInstructionsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFollowInstructionsGameMode::AFollowInstructionsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
