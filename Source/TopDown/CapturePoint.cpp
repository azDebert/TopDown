// Fill out your copyright notice in the Description page of Project Settings.

#include "CapturePoint.h"
#include "Components/SphereComponent.h"
#include "Ship.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
ACapturePoint::ACapturePoint()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapturePointMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapturePointMeshComponent"));
	RootComponent = CapturePointMeshComponent;

	CaptureZoneComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CaptureZoneComponent"));
	CaptureZoneComponent->SetupAttachment(CapturePointMeshComponent);
	CaptureZoneComponent->SetSphereRadius(500.f);
	CaptureZoneComponent->OnComponentBeginOverlap.AddDynamic(this, &ACapturePoint::OnOverlapBegin);
    CaptureZoneComponent->OnComponentEndOverlap.AddDynamic(this, &ACapturePoint::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACapturePoint::BeginPlay()
{
	Super::BeginPlay();

	Ship = Cast<AShip>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// When ship enters the capture zone, start timer and capture point
void ACapturePoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShip* OverlappingShip = Cast<AShip>(OtherActor);
	if (OverlappingShip)
	{
		if (OverlappingShip->bAlive)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Ship overlapping"));
			if (!GetWorld()->GetTimerManager().IsTimerActive(CaptureTimerHandle))
			{
				GetWorld()->GetTimerManager().SetTimer(CaptureTimerHandle, this, &ACapturePoint::OnCaptureComplete, 5.0f, false);
				//UE_LOG(LogTemp, Warning, TEXT("Timer started"));
			}
		}
	}
}

// When ship leaves the capture zone, stop timer
void ACapturePoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AShip* OverlappingShip = Cast<AShip>(OtherActor);
	if (OverlappingShip)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Ship left capture zone"));
	}
}

// Called every frame
void ACapturePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACapturePoint::HandleDeath()
{
	Destroy();

	if (CaptureSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CaptureSound, GetActorLocation());
	}
}

void ACapturePoint::OnCaptureComplete()
{
	HandleDeath();
	//UE_LOG(LogTemp, Warning, TEXT("Capture complete"));
}