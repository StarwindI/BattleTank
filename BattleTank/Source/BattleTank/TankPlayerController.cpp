// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetContolledTank();
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController: tank %s is ready!"), *tank->GetName())
	} else {
		UE_LOG(LogTemp, Error, TEXT("PlayerController: tank not found!"))
	}
}

ATank* ATankPlayerController::GetContolledTank() const
{
	return Cast<ATank>(GetPawn());
}
