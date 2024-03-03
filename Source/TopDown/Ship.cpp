// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AShip::AShip()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // Inputs
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShip::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AShip::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AShip::Fire);
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShipPlayerController) // Get result under cursor, rotate gun to that point
	{
		FHitResult TraceHitResult;
		ShipPlayerController->GetHitResultUnderCursor(
			ECC_Visibility,
			false,
			TraceHitResult);

		/*DrawDebugSphere(
			GetWorld(),
			TraceHitResult.ImpactPoint,
			25.f,
			12,
			FColor::Black,
			false,
			-1.f);*/ //ds

		RotateGun(TraceHitResult.ImpactPoint);
	}
}

void AShip::HandleDeath()
{
	// Destroy the ship and end the game
	Super::HandleDeath();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	bAlive = false;
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();

	ShipPlayerController = Cast<APlayerController>(GetController());
}

void AShip::Move(float Value) // Calculates new position based on the input, based on frame rate and ship speed
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * ShipSpeed * GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(DeltaLocation, true);
	//UE_LOG(LogTemp, Warning, TEXT("Move: %f"), Value);
}

void AShip::Turn(float Value) // Calculates new rotation based on the input, based on frame rate and turn speed
{
	FRotator DeltaRotation = FRotator::ZeroRotator; 
	DeltaRotation.Yaw = Value * TurnSpeed * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(DeltaRotation, true);
	//UE_LOG(LogTemp, Warning, TEXT("Turn: %f"), Value);
}

void AShip::SetShipSpeed(float NewSpeed)
{
	ShipSpeed = NewSpeed;
}

float AShip::GetShipSpeed() const
{
	return ShipSpeed;
}