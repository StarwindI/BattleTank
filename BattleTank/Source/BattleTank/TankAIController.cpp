// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetContolledTank();
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController: tank %s is ready!"), *tank->GetName())
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIController: tank not found!"))
	}
}

ATank* ATankAIController::GetContolledTank() const
{
	return Cast<ATank>(GetPawn());
}



