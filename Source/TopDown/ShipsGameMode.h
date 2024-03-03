// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShipsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API AShipsGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	// Function to call when an actor dies to handle game over conditions
	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	// Start game function, starts with a delay and displays a widget on the screen
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	// Win or lose game function, displays a widget on the screen
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bGameWon);

private:

	// References to the ship and player controller
	class AShip* Ship;
	class AShipPlayerController* ShipPlayerController;

	// Delay before the game starts to read instructions
	float StartDelay = 15.f;

	// Function to handle the game start after the delay has passed
	void HandleGameStart();

	// Function to check if the player has won yet
	void CheckGameOverConditions();

	// Used to check if the game is over
	int32 TargetEnemies = 0;
	int32 GetTargetEnemyCount();

	int32 TargetCaptures = 0;
    int32 GetTargetCaptureCount();
};
