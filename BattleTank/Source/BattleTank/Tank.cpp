#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"

ATank::ATank() {
	PrimaryActorTick.bCanEverTick = false;
//	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::BeginPlay() {
	Super::BeginPlay();
	FireTime = FPlatformTime::Seconds();
	TankMovementComponent = FindComponentByClass<UTankMovementComponent>();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::SetTurret(UTankTurret* ATurret) {
	if (TankAimingComponent) {
		TankAimingComponent->SetTurret(ATurret);
	}
}

void ATank::SetBarrel(UTankBarrel* ABarrel) {
	Barrel = ABarrel;
	if (TankAimingComponent) {
		TankAimingComponent->SetBarrel(ABarrel);
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
	else {
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
