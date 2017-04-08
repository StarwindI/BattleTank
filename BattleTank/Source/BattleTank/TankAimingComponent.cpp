// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() 
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LounchSpeed, FColor TraceColor) const
{
	FVector OutLounchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLounchVelocity,
			StartLocation,
			HitLocation,
			LounchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
	   )
	) {
		FVector AimDirection = OutLounchVelocity.GetSafeNormal();
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

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* ABarrel)
{
	Barrel = ABarrel;
}
