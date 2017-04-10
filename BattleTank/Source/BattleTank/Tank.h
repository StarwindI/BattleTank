// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation, FColor TraceColor) const;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* ABarrel);

	UPROPERTY(EditAnywhere, Category = Firing)
		float LounchSpeed = 10000.0f;
	UPROPERTY(EditAnywhere, Category = Firing)
		float DistanceRange = 300000.0f;

};
