#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	FVector ForceApplied = Throttle * GetForwardVector() * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	// TODO find actual altitude Z
	ForceLocation.Z += 100.0f;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


