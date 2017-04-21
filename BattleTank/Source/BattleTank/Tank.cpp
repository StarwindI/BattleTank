#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"

ATank::ATank() {
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();
	FireTime = FPlatformTime::Seconds();
	TankMovementComponent = FindComponentByClass<UTankMovementComponent>();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (TankAimingComponent) {
		Barrel = TankAimingComponent->GetBarrel();
	}
}

FVector ATank::GetBarrelStartLocation() const {
	if (Barrel) {
		return Barrel->GetSocketLocation(FName("Projectile"));
	}
	else {
		return FVector(0);
	}
}

bool ATank::AimAt(FVector HitLocation) const {
	if (TankAimingComponent) {
		return TankAimingComponent->AimAt(HitLocation, LounchSpeed, DistanceRange);
	} else {
		return false;
	}
}

void ATank::Fire() {
	if (Barrel && FPlatformTime::Seconds() >= FireTime + ReloadTime) {
		AProjectile* Projectile =
			GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LounchSpeed);
		FireTime = FPlatformTime::Seconds();
	}
}

void ATank::MoveTo(AActor* Goal, float AcceptanceRadius) {
	if (TankMovementComponent && Goal) {
		FVector MoveVelocity = Goal->GetActorLocation() - GetActorLocation();
		TankMovementComponent->RequestDirectMove(MoveVelocity, false);
	}
}

bool ATank::RotateTo(AActor* Goal) {
	if (TankMovementComponent && Goal) {
		FVector MoveVelocity = Goal->GetActorLocation() - GetActorLocation();
		return TankMovementComponent->RequestDirectRotate(MoveVelocity, false);
	} else {
		return false;
	}
}
