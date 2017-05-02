#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 20;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		int ProjectileCount = 20;

	void Turn(float RelativeSpeed);
};
