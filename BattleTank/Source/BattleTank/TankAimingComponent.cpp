#include "BattleTank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

UTankAimingComponent::UTankAimingComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	FireTime = FPlatformTime::Seconds();
	FiringState = EFiringState::Reloading;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::SetTurretBarrel(UTankTurret* ATurret, UTankBarrel* ABarrel) {
	Turret = ATurret;
	Barrel = ABarrel;
}

int UTankAimingComponent::GetProjectileCount() {
	return Turret->ProjectileCount;
}

EFiringState UTankAimingComponent::CheckState(bool is_elevated, bool is_reloaded) {
	if (Turret->ProjectileCount == 0) {
		FiringState = EFiringState::Empty;
	} else
	if (!is_reloaded) {
		FiringState = EFiringState::Reloading;
	} else 
	if (!is_elevated) {
			FiringState = EFiringState::Aiming;
	} else {
		FiringState = EFiringState::Ready;
	}
	return FiringState;
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
	
	Turret->Turn(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
	return CheckState(AimDirection.Equals(Barrel->GetForwardVector().GetSafeNormal(), 0.01f), FPlatformTime::Seconds() >= FireTime + ReloadTime) != EFiringState::Aiming;
}

bool UTankAimingComponent::DistanceAt(FVector HitLocation) {
	if (ensure(Barrel)) {
		return FVector::Distance(Barrel->GetSocketLocation(FName("Projectile")), HitLocation) <= DistanceShot;
	}	else {
		return false;
	}
}

bool UTankAimingComponent::Reloaded() {
	return CheckState(FiringState != EFiringState::Aiming, FPlatformTime::Seconds() >= FireTime + ReloadTime) != EFiringState::Reloading;
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
	if (ensure(Barrel) && ensure(ProjectileBlueprint) && Reloaded() && Turret->ProjectileCount > 0) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		Projectile->LaunchProjectile(LounchSpeed);
		FireTime = FPlatformTime::Seconds();
		Turret->ProjectileCount--;
	}
}
