// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetContolledTank(false);
	EnemyTank = GetContolledTank(true);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsEnenmyTank();

	ControlledTank->Fire();

}

ATank* ATankAIController::GetContolledTank(bool _player) 
{
	ATank* result;
	if (_player) {
		result = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()); 
	} else {
		result = Cast<ATank>(GetPawn());
	}
	if (result) {
		if (_player) {
			UE_LOG(LogTemp, Warning, TEXT("AIController: player tank %s was found at location %s"), *result->GetName(), *result->GetActorLocation().ToString())
		} else {
			UE_LOG(LogTemp, Warning, TEXT("AIController: tank %s is ready at location %s"), *result->GetName(), *result->GetActorLocation().ToString())
		}
		return result;
	} else {
		if (_player) {
			UE_LOG(LogTemp, Error, TEXT("AIController: player tank not found!"))
		} else {
			UE_LOG(LogTemp, Error, TEXT("AIController: tank not found!"))
		}
		return nullptr;
	}
}

void ATankAIController::AimTowardsEnenmyTank()
{
	if (EnemyTank) {
		FVector HitLocation;
		if (GetSightRayHitLocation(HitLocation)) {
			ControlledTank->AimAt(HitLocation);
		}
	}
}

bool ATankAIController::GetSightRayHitLocation(FVector& HitLocation) const
{
	if (EnemyTank) {
		HitLocation = EnemyTank->GetActorLocation();
		return true;
	} else {
		HitLocation = FVector(0);
		return false;
	}
}

