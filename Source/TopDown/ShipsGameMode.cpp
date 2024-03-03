// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipsGameMode.h"
#include "Ship.h"
#include "ShipPlayerController.h"
#include "EnemyShip.h"
#include "CapturePoint.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AShipsGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Ship)
    {
        Ship->HandleDeath();
        if (ShipPlayerController)
        {
            Ship->DisableInput(Ship->GetShipPlayerController()); // Optional
            Ship->GetShipPlayerController()->bShowMouseCursor = false; // Optional, game ends after a few seconds anyway
            ShipPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false); // Player lost
    }
    else if (AEnemyShip* DestroyedEnemyShip = Cast<AEnemyShip>(DeadActor)) // Once an enemy ship is destroyed, decrement the count
    {
        DestroyedEnemyShip->HandleDeath();
        --TargetEnemies;
        //UE_LOG(LogTemp, Warning, TEXT("TargetEnemies: %d"), TargetEnemies);
        if (TargetEnemies == 0)
        {
			CheckGameOverConditions();
		}
    }
    else if (ACapturePoint* DestroyedCapturePoint = Cast<ACapturePoint>(DeadActor)) // Once a capture point is destroyed, decrement the count
    {
        DestroyedCapturePoint->HandleDeath();
        --TargetCaptures;
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AShipsGameMode::CheckGameOverConditions, 0.5f, false); // Timer in case the capture point was destroyed by the player but the game is not over
        if (TargetCaptures == 0)
        {
            CheckGameOverConditions();
        }
    }
    FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AShipsGameMode::BeginPlay); // Timer to restart the game
}

void AShipsGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AShipsGameMode::HandleGameStart()
{
    TargetEnemies = GetTargetEnemyCount();
    //UE_LOG(LogTemp, Warning, TEXT("TargetEnemies: %d"), TargetEnemies);
    TargetCaptures = GetTargetCaptureCount();
    //UE_LOG(LogTemp, Warning, TEXT("TargetCaptures: %d"), TargetCaptures);

    Ship = Cast<AShip>(UGameplayStatics::GetPlayerPawn(this, 0));
    ShipPlayerController = Cast<AShipPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    // Disable player input while the game is starting, enable it after a delay
    if (ShipPlayerController)
    {
        ShipPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ShipPlayerController, &AShipPlayerController::SetPlayerEnabledState, true);

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
    }
}

int32 AShipsGameMode::GetTargetEnemyCount() // Gets the number of enemy ships left in the level
{
	TArray<AActor*> EnemyShips;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemyShip::StaticClass(), EnemyShips);
	return EnemyShips.Num();
}

int32 AShipsGameMode::GetTargetCaptureCount() // Gets the number of capture points left in the level
{
	TArray<AActor*> CapturePoints;
	UGameplayStatics::GetAllActorsOfClass(this, ACapturePoint::StaticClass(), CapturePoints);
	return CapturePoints.Num();
}

void AShipsGameMode::CheckGameOverConditions()
{
    // If no enemies or capture points are left, the game is over, player wins
    if (GetTargetEnemyCount() == 0 && GetTargetCaptureCount() == 0)
    {
        GameOver(true);
    }
}