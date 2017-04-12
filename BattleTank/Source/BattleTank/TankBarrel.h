#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 10;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevationDegrees = 40;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevationDegrees = 0;

	void Elevate(float RelativeSpeed);
};
