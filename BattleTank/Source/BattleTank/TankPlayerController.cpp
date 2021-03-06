#include "BattleTank.h"
#include "Healthy.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetPawn()) {
		AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (AimingComponent) {
			FoundAimingComponent(AimingComponent);
		}
	} else {
		AimingComponent = nullptr;
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ALive) {
		AimTowardsCrosshair();
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		AHealthy* PossessedHealthy = Cast<AHealthy>(InPawn);
		if (ensure(PossessedHealthy)) {
			PossessedHealthy->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnDeath);
		}
	}
}

void ATankPlayerController::OnDeath() {
	ALive = false;
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (AimingComponent) {
		FVector HitLocation;
		if (GetSightRayHitLocation(HitLocation)) {
			AimingComponent->AimAt(HitLocation);
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
	if (!ensure(AimingComponent)) { return false; }
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * AimingComponent->DistanceLook;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Camera)) {
		HitLocation = HitResult.Location;
		return true;
	} else {
		HitLocation = FVector(0);
		return false;
	}
}
