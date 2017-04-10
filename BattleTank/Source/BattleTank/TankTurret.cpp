// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Turn(float RelativeSpeed)
{
	float TurningChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewTurning = RelativeRotation.Yaw + TurningChange;
	SetRelativeRotation(FRotator(0.0f, RawNewTurning, 0.0f));
}



