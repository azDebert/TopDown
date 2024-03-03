// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipPlayerController.h"
#include "GameFramework/Pawn.h"

void AShipPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	// Enable the player if in game, once the game is over the player will be disabled
	if (bPlayerEnabled) 
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}