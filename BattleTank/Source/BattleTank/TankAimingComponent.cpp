// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() 
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetTurret(UTankTurret* ATurret)
{
	Turret = ATurret;
}

void UTankAimingComponent::SetBarrel(UTankBarrel* ABarrel)
{
	Barrel = ABarrel;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LounchSpeed, float DistanceRange)
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
		float TargetDistance = FVector::Distance(StartLocation, HitLocation);
		FColor TraceColor;
		if (TargetDistance <= DistanceRange) {
			TraceColor = FColor(0, 0, 255);
		} else {
			TraceColor = FColor(255, 0, 0);
		}
//		float Time = GetWorld()->GetTimeSeconds();
//		UE_LOG(LogTemp, Warning, TEXT("%f UTankAimingComponent: %f"), Time, TargetDistance)
		FVector AimDirection = OutLounchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			HitLocation,
			TraceColor,
			false,
			0.0f,
			0.0f,
			3.0f
		);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	if (FMath::Abs(DeltaRotator.Yaw) > DeltaRotator.Yaw + 360) {
		DeltaRotator.Yaw += 360;
	}

//	UE_LOG(LogTemp, Warning, TEXT("Barrel: %f Aim %f Delta %f"), BarrelRotator.Yaw, AimAsRotator.Yaw, DeltaRotator.Yaw)

	Turret->Turn(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}
