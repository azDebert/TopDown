// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupSpeed.h"
#include "Ship.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
APickupSpeed::APickupSpeed()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMeshComponent"));
	RootComponent = PickupMeshComponent;

	TriggerPickupComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerPickupComponent"));
	TriggerPickupComponent->SetupAttachment(PickupMeshComponent);
	TriggerPickupComponent->SetSphereRadius(500.f);
	TriggerPickupComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupSpeed::OnOverlapBegin);
	TriggerPickupComponent->OnComponentEndOverlap.AddDynamic(this, &APickupSpeed::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APickupSpeed::BeginPlay()
{
	Super::BeginPlay();

	Ship = Cast<AShip>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// When ship overlaps the pickup zone, apply speed boost
void APickupSpeed::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AShip* OverlappingShip = Cast<AShip>(OtherActor);
	if (OverlappingShip && OverlappingShip->bAlive)
	{
		float OriginalSpeed = OverlappingShip->GetShipSpeed();
		OverlappingShip->DefaultShipSpeed = OriginalSpeed; // Save the original speed for later
		OverlappingShip->SetShipSpeed(OriginalSpeed * SpeedBoostMultiplier); // Apply speed boost

		// Start a timer to reset the speed after 5 seconds
		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [OverlappingShip, this]() 
			{
			// Reset the speed after the boost duration
			OverlappingShip->SetShipSpeed(OverlappingShip->DefaultShipSpeed);
			Destroy();
			}, SpeedBoostDuration, false);

		if (PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		}

		// Actor should be destroyed but just in case
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}

void APickupSpeed::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AShip* OverlappingShip = Cast<AShip>(OtherActor);
	if (OverlappingShip)
	{
		// used to check for errors if needed
	}
}

// Called every frame
void APickupSpeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}