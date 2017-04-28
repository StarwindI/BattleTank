#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	float CurrentThrottle = 0;
	UTankTrack();
	void ApplaySidewaysForce(float DeltaTime);

public:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingForce = 30000000.0f;
	
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetThrottle(float Throttle);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	virtual void BeginPlay() override;
	void DriveTrack();
};
