// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
//	UE_LOG(LogTemp, Warning, TEXT("UTankBarrel::Elevate %f"), DegreePerSecond)
	float ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees), 0.0f, 0.0f));
}

void UTankBarrel::Turn(float RelativeSpeed)
{
	float TurningChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	UStaticMeshComponent* turret = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
//	UE_LOG(LogTemp, Warning, TEXT("TankBarrel: owner name is %s"), *GetOwner()->GetName())
	if (turret) {
		float RawNewTurning = turret->RelativeRotation.Yaw + TurningChange;
		turret->SetRelativeRotation(FRotator(0.0f, RawNewTurning, 0.0f));
	}
}


