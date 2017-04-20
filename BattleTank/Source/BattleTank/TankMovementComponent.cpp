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

void UTankMovementComponent::IntendMove(FVector TargetLocation) {
	FVector SelfForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FRotator DeltaRotator = SelfForward.Rotation() - TargetLocation.Rotation();
	LeftTrack->SetThrottle(FMath::Cos(DeltaRotator.Yaw) - FMath::Sin(DeltaRotator.Yaw));
	RightTrack->SetThrottle(FMath::Cos(DeltaRotator.Yaw) + FMath::Sin(DeltaRotator.Yaw));
}

void UTankMovementComponent::IntendRotate(FVector TargetLocation) {
	FVector SelfForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FRotator DeltaRotator = SelfForward.Rotation() - TargetLocation.Rotation();
	LeftTrack->SetThrottle(-FMath::Sin(DeltaRotator.Yaw));
	RightTrack->SetThrottle(FMath::Sin(DeltaRotator.Yaw));
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	IntendMove(MoveVelocity.GetSafeNormal());
}

void UTankMovementComponent::RequestDirectRotate(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	IntendRotate(MoveVelocity.GetSafeNormal());
}