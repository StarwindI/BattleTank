#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float TrackMaxDrivingForce = 100000.0f;

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetThrottle(float Throttle);
};
