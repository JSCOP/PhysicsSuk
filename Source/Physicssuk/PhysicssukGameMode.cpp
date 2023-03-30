// Copyright Epic Games, Inc. All Rights Reserved.

#include "PhysicssukGameMode.h"
#include "PhysicssukCharacter.h"
#include "UObject/ConstructorHelpers.h"

APhysicssukGameMode::APhysicssukGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
