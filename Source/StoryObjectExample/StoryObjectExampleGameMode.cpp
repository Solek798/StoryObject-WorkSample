// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoryObjectExampleGameMode.h"
#include "StoryObjectExampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStoryObjectExampleGameMode::AStoryObjectExampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
