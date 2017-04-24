#include "BattleTank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

UTankAimingComponent::UTankAimingComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetTurretBarrel(UTankTurret* ATurret, UTankBarrel* ABarrel) {
	Turret = ATurret;
	Barrel = ABarrel;
}

bool UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	if (DeltaRotator.Yaw > 180) {
		DeltaRotator.Yaw -= 360;
	}
	if (DeltaRotator.Yaw < -180) {
		DeltaRotator.Yaw += 360;
	}
	bool is_elevated = FMath::Abs(DeltaRotator.Pitch) < 1;
	Turret->Turn(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
	/*	трассировка взгляда
	FHitResult HitResult;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector EndLocation = StartLocation + Barrel->GetForwardVector() * DistanceLook;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility)) {
	HitResult.Actor;
	}
	*/
	return FMath::Abs(DeltaRotator.Yaw) < 1 && FMath::Abs(DeltaRotator.Pitch) < 1;
}

bool UTankAimingComponent::DistanceAt(FVector HitLocation) {
	if (ensure(Barrel)) {
		return FVector::Distance(Barrel->GetSocketLocation(FName("Projectile")), HitLocation) <= DistanceShot;
	}	else {
		return false;
	}
}

bool UTankAimingComponent::AimAt(FVector HitLocation) {
	FVector OutLounchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLounchVelocity,
		StartLocation,
		HitLocation,
		LounchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution) {
		FVector AimDirection = OutLounchVelocity.GetSafeNormal();
		return MoveBarrelTowards(AimDirection);
	} else {
		return false;
	}
}

void UTankAimingComponent::Fire() {
	if (Barrel && FPlatformTime::Seconds() >= FireTime + ReloadTime) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		Projectile->LaunchProjectile(LounchSpeed);
		FireTime = FPlatformTime::Seconds();
	}
}
