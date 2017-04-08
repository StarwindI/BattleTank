// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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
			UE_LOG(LogTemp, Warning, TEXT("AIController: player tank %s was found!"), *result->GetName())
		} else {
			UE_LOG(LogTemp, Warning, TEXT("AIController: tank %s is ready!"), *result->GetName())
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
	if (!EnemyTank) {
		EnemyTank = GetContolledTank(true);
	}
	if (EnemyTank) {
		FVector HitLocation;
		if (GetSightRayHitLocation(HitLocation)) {
			ControlledTank->AimAt(HitLocation, FColor(255, 0, 0));
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

