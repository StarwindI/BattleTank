#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};


class UTankTurret;
class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY() 

private:

protected:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = Setup)
		EFiringState FiringState = EFiringState::Reloading;

	bool MoveBarrelTowards(FVector AimDirection);

public:	
	UTankAimingComponent();

	bool AimAt(FVector HitLocation, float LounchSpeed, float DistanceRange);
	void SetTurret(UTankTurret* ATurret);
	void SetBarrel(UTankBarrel* ABarrel);
};
