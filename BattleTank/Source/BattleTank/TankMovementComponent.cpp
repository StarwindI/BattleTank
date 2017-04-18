#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::SetTracks(UTankTrack* ALeftTrack, UTankTrack* ARightTrack) {
	LeftTrack = ALeftTrack;
	RightTrack = ARightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw) {
	LeftTrack->SetThrottle(-Throw / 2);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw / 2);
}
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	UE_LOG(LogTemp, Warning, TEXT("tank %s vectoring to %s"), *GetOwner()->GetName(), *MoveVelocity.ToString())
}