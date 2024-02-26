// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownBasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"	
#include "DrawDebugHelpers.h"

// Sets default values
ATopDownBasePawn::ATopDownBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetupAttachment(RootComponent);

	ShipGunMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipGunMesh"));
	ShipGunMeshComponent->SetupAttachment(ShipMeshComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(ShipGunMeshComponent);

}

void ATopDownBasePawn::RotateGun(FVector LookAtTarget) // Rotate gun to look at target, either player or cursor
{
	FVector ToTarget = LookAtTarget - ShipGunMeshComponent->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	ShipGunMeshComponent->SetWorldRotation(LookAtRotation);
}

void ATopDownBasePawn::Fire() // Draw debug sphere on projectile spawn point, later projectile fire
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	DrawDebugSphere(
		GetWorld(),
		ProjectileSpawnPointLocation,
		25.f,
		12,
		FColor::Black,
		false,
		3.f);
}
