// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOPDOWN_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Static mesh for the projectile and its movement component
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMeshComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	// When projectile hits something
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 25.f;

	// Particles for the projectile
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticle;
    UPROPERTY(EditAnywhere, Category = "Combat")
    class UParticleSystemComponent* TrailParticle;

	// Sounds for the projectile
    UPROPERTY(EditAnywhere, Category = "Combat")
    USoundBase* LaunchSound;
    UPROPERTY(EditAnywhere, Category = "Combat")
    USoundBase* HitSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};