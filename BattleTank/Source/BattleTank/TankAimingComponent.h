#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankTurret;
class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY() 

protected:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;

	bool MoveBarrelTowards(FVector AimDirection);

public:	
	UTankAimingComponent();

	bool AimAt(FVector HitLocation, float LounchSpeed, float DistanceRange);
	void SetTurret(UTankTurret* ATurret);
	void SetBarrel(UTankBarrel* ABarrel);
};
