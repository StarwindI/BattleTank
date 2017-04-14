#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"

ATank::ATank() {
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
//	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::BeginPlay() {
	Super::BeginPlay();
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::SetTurret(UTankTurret* ATurret) {
	TankAimingComponent->SetTurret(ATurret);
}

void ATank::SetBarrel(UTankBarrel* ABarrel) {
	Barrel = ABarrel;
	TankAimingComponent->SetBarrel(ABarrel);
}

FVector ATank::GetBarrelStartLocation() const {
	if (Barrel) {
		return Barrel->GetSocketLocation(FName("Projectile"));
	}
	else {
		return FVector(0);
	}
}

void ATank::MoveTo(FVector HitLocation) const {
}

bool ATank::AimAt(FVector HitLocation) const {
	return TankAimingComponent->AimAt(HitLocation, LounchSpeed, DistanceRange);
}

void ATank::Fire() {
	if (FPlatformTime::Seconds() >= NextFireTime && Barrel) {
		AProjectile* Projectile =
			GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
			);
		NextFireTime = FPlatformTime::Seconds() + ReloadTime;
		Projectile->LaunchProjectile(LounchSpeed);
	}
}

