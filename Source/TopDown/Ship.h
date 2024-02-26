// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownBasePawn.h"
#include "Ship.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API AShip : public ATopDownBasePawn
{
	GENERATED_BODY()
	
public:
	AShip();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ShipSpeed = 420.f;

    UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 180.f;

	void Move(float Value);

	void Turn(float Value);

	APlayerController* PlayerControllerRef;
};
