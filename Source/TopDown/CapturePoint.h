// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CapturePoint.generated.h"

UCLASS()
class TOPDOWN_API ACapturePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACapturePoint();
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components for the capture point, static and sphere to detect overlap
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* CapturePointMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* CaptureZoneComponent;

	// Called when the ship goes in and out of the zone
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Completed capture function
	void OnCaptureComplete();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Destroys point once captured
	void HandleDeath();

private:

	// Reference to ship, used to check if the ship is in the zone
	class AShip* Ship;

	// Capture timer
	FTimerHandle CaptureTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* CaptureSound;
};