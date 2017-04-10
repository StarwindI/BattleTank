// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetContolledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController: tank %s is ready!"), *ControlledTank->GetName())
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
	if (ControlledTank) {
		FVector HitLocation;
		if (GetSightRayHitLocation(HitLocation)) {
//			UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
			ControlledTank->AimAt(HitLocation, FColor(0, 0, 255));
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);
	FVector2D ScreenLocation = FVector2D(CrosshairXLocation * SizeX, CrosshairYLocation * SizeY);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	} else {
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLoction;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLoction, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation;
	StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * ControlledTank->DistanceRange;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	} else {
		HitLocation = FVector(0);
		return false;
	}
}

