// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShipPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API AShipPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	// Enable or disable player input
	void SetPlayerEnabledState(bool bPlayerEnabled);
};