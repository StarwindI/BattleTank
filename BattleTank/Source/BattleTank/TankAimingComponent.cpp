// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() 
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrel(UTankBarrel* ABarrel)
{
	Barrel = ABarrel;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LounchSpeed, FColor TraceColor) 
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
	Barrel->Elevate(5);
}
