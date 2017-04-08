// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	ATank* ControlledTank;
	ATank* EnemyTank;
	ATank* GetContolledTank(bool _player);
	void AimTowardsEnenmyTank();
	bool GetSightRayHitLocation(FVector& HitLocation) const;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		float DistanceRange = 1000000.0f;
};
