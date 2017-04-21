#include "BattleTank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

UTankAimingComponent::UTankAimingComponent() 
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetTurret(UTankTurret* ATurret)
{
	Turret = ATurret;
}

void UTankAimingComponent::SetBarrel(UTankBarrel* ABarrel)
{
	Barrel = ABarrel;
}

bool UTankAimingComponent::AimAt(FVector HitLocation, float LounchSpeed, float DistanceRange)
{
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
/*
		FVector EndLocation = StartLocation + Barrel->GetForwardVector().GetSafeNormal() * DistanceRange;
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			FColor(255, 0, 0),
			false,
			0.0f,
			0.0f,
			3.0f
		);
*/
		FVector AimDirection = OutLounchVelocity.GetSafeNormal();
		return MoveBarrelTowards(AimDirection);
	} else {
		return false;
	}
}

bool UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
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
