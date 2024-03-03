// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownBasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"	
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"
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

void ATopDownBasePawn::HandleDeath()
{
	// Death Effects
	if (DeathParticle)
    {
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
}

void ATopDownBasePawn::RotateGun(FVector LookAtTarget)
{
	// Rotate the gun to look at the target location, only on the yaw axis as the gun does not need to rotate up or down
	FVector ToTarget = LookAtTarget - ShipGunMeshComponent->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	ShipGunMeshComponent->SetWorldRotation(LookAtRotation);
}

void ATopDownBasePawn::Fire() 
{
	// Get the location and rotation of the projectile and spawn it
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLocation, ProjectileSpawnRotation);
	Projectile->SetOwner(this);

	/*DrawDebugSphere(
		GetWorld(),
		ProjectileSpawnPointLocation,
		25.f,
		12,
		FColor::Black,
		false,
		3.f);*/ //ds
}