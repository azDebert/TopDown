// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownBasePawn.generated.h"

UCLASS()
class TOPDOWN_API ATopDownBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATopDownBasePawn();

	void HandleDeath();

protected:

	// Rotate gun to look at target, either player or cursor
	void RotateGun(FVector LookAtTarget);

	// Fire a projectile
	void Fire();

private: 

	// Components for the player ship as well as the enemy ships
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipGunMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileSpawnPoint;

	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	// Death effects
    UPROPERTY(EditAnywhere, Category = "Combat")
    class UParticleSystem* DeathParticle;
    UPROPERTY(EditAnywhere, Category = "Combat")
    class USoundBase* DeathSound;
};