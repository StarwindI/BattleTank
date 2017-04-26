#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UTankTrack();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingForce = 100000.0f;

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetThrottle(float Throttle);
};
