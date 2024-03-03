// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpeed.generated.h"

UCLASS()
class TOPDOWN_API APickupSpeed : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupSpeed();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components for the for the pickup actor
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* PickupMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* TriggerPickupComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// Speed Boost Variables
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float SpeedBoostMultiplier = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float SpeedBoostDuration = 5.f;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Reference to ship
	class AShip* Ship;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* PickupSound;
};