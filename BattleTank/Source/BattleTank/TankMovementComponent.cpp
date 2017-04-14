#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::SetTracks(UTankTrack* ALeftTrack, UTankTrack* ARightTrack) {
	LeftTrack = ALeftTrack;
	RightTrack = ARightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
//	UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

