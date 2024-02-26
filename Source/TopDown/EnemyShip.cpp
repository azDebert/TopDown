// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShip.h"
#include "Ship.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AEnemyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInFireRange()) // If the player is in range, rotate the gun to face the player
	{
        RotateGun(Ship->GetActorLocation());
	}
}

// Called when the game starts or when spawned
void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();

    Ship = Cast<AShip>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyShip::CheckFireCondition, FireRate, true); // Fire every FireRate seconds
}

void AEnemyShip::CheckFireCondition() // Check if the player is in range and fire
{
    if (bInFireRange())
    {
        Fire();
    }
}

bool AEnemyShip::bInFireRange() // Check if the player is in range
{
    if (Ship)
    {
        float Distance = FVector::Dist(GetActorLocation(), Ship->GetActorLocation());
        if (Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}