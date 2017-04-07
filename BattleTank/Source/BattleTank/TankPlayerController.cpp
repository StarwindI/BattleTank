// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetContolledTank();
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController: tank %s is ready!"), *tank->GetName())
	} else {
		UE_LOG(LogTemp, Error, TEXT("PlayerController: tank not found!"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetContolledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetContolledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLoction) const
{
	FVector WorldLoction;
	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);
	FVector2D ScreenLocation = FVector2D(CrosshairXLocation * SizeX, CrosshairYLocation * SizeY - 10);
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLoction, HitLoction);

	HitLoction *= 20000;
	FVector Position;
	FRotator Rotattion;
	GetPlayerViewPoint(OUT Position, OUT Rotattion);
	FVector TraceEnd = Position + Rotattion.Vector() * 1000;

	DrawDebugLine(
		GetWorld(),
		TraceEnd,
		HitLoction,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		2.0f
	);

	return true;
}