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
	if (DeltaRotator.Yaw > 180) {
		DeltaRotator.Yaw -= 360;
	}
	if (DeltaRotator.Yaw < -180) {
		DeltaRotator.Yaw += 360;
	}
	LeftTrack->SetThrottle(FMath::Cos(DeltaRotator.Yaw / 180 * 3.1415926) - FMath::Sin(DeltaRotator.Yaw / 180 * 3.1415926));
	RightTrack->SetThrottle(FMath::Cos(DeltaRotator.Yaw / 180 * 3.1415926) + FMath::Sin(DeltaRotator.Yaw / 180 * 3.1415926));
}

bool UTankMovementComponent::IntendRotate(FVector TargetLocation) {
	FVector SelfForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FRotator DeltaRotator = SelfForward.Rotation() - TargetLocation.Rotation();
	if (DeltaRotator.Yaw > 180) {
		DeltaRotator.Yaw -= 360;
	}
	if (DeltaRotator.Yaw < -180) {
		DeltaRotator.Yaw += 360;
	}
	LeftTrack->SetThrottle(-FMath::Sin(DeltaRotator.Yaw / 180 * 3.1415926));
	RightTrack->SetThrottle(FMath::Sin(DeltaRotator.Yaw / 180 * 3.1415926));
	return FMath::Abs(DeltaRotator.Yaw) < 10;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	IntendMove(MoveVelocity.GetSafeNormal());
}

bool UTankMovementComponent::RequestDirectRotate(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	return IntendRotate(MoveVelocity.GetSafeNormal());
}