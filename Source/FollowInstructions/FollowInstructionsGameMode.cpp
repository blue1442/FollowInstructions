// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FollowInstructionsGameMode.h"
#include "FollowInstructionsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFollowInstructionsGameMode::AFollowInstructionsGameMode()
{
	//APawn, then UObject
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FollowInstructions/Blueprints/MainCharBps/MainChar_BP"));
	static ConstructorHelpers::FClassFinder<UObject> PlayerHUDClass(TEXT("/Game/FollowInstructions/Blueprints/MainCharBps/Hud"));

	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("TCould not find default player pawn class, was the file moved by gnomes?"));
	}

	if (PlayerHUDClass.Class != NULL) {
		HUDClass = PlayerHUDClass.Class;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TCould not find default player hud class, was the file moved by gnomes?"));
	}
}
