// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetContolledTank(false);
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController: tank %s is ready!"), *tank->GetName())
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIController: tank not found!"))
	}
	ATank* enemy_tank = GetContolledTank(true);
	if (enemy_tank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController: player tank %s was found!"), *enemy_tank->GetName())
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIController: player tank not found!"))
	}
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
		return result;
	} else {
		return nullptr;
	}
}



