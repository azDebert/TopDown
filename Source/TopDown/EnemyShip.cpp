// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyShip.h"
#include "Ship.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void AEnemyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInFireRange()) // If the player is in range, rotate the gun to face the player
	{
        RotateGun(Ship->GetActorLocation());
	}
}

void AEnemyShip::HandleDeath()
{
    Super::HandleDeath();
    Destroy();
}

// Called when the game starts or when spawned
void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();
    Ship = Cast<AShip>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyShip::CheckFireCondition, FireRate, true); 
}

void AEnemyShip::CheckFireCondition()
{
    if (Ship == nullptr)
    {
        return;
    }
    if (bInFireRange() && Ship->bAlive)
	{
		Fire();
    }
}

bool AEnemyShip::bInFireRange() 
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