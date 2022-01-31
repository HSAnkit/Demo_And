// Copyright Epic Games, Inc. All Rights Reserved.

#include "IOS_DEMOGameMode.h"
#include "IOS_DEMOCharacter.h"

AIOS_DEMOGameMode::AIOS_DEMOGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AIOS_DEMOCharacter::StaticClass();	
}
