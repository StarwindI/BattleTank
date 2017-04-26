#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectAcceleration / 2;
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle) {
	FVector ForceApplied = Throttle * GetForwardVector() * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
// TODO find actual altitude Z
	ForceLocation.Z += 100.0f;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


