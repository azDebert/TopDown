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

protected:
	
	virtual void BeginPlay() override;

private:

	class AShip* Ship;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 1000.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 3.f;
	void CheckFireCondition();

	bool bInFireRange();

};
