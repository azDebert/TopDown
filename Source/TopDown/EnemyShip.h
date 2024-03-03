// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownBasePawn.h"
#include "EnemyShip.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API AEnemyShip : public ATopDownBasePawn
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

	// Destroy the enemy ship
	void HandleDeath();

protected:
	
	virtual void BeginPlay() override;

private:

	// Reference to the player
	class AShip* Ship;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 600.f;

	// Fire every few seconds
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;

	// Check if the enemy is in range to fire at the player
	void CheckFireCondition();

	// Check if the player is in range
	bool bInFireRange();

};