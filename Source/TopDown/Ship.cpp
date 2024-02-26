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

void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShip::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AShip::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AShip::Fire);
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef) // Get result under cursor, rotate gun to that point
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(
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

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void AShip::Move(float Value) // Calculates new position based on the input, based on frame rate and ship speed
{
	UE_LOG(LogTemp, Warning, TEXT("Move: %f"), Value);

	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * ShipSpeed * GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(DeltaLocation, true);

}

void AShip::Turn(float Value) // Calculates new rotation based on the input, based on frame rate and turn speed
{
	UE_LOG(LogTemp, Warning, TEXT("Turn: %f"), Value);

	FRotator DeltaRotation = FRotator::ZeroRotator; 
	DeltaRotation.Yaw = Value * TurnSpeed * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(DeltaRotation, true);
}