// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownGameMode.h"
#include "TopDownPawn.h"

ATopDownGameMode::ATopDownGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ATopDownPawn::StaticClass();
}

