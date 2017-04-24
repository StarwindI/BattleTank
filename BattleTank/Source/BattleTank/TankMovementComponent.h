#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	void IntendMove(FVector TargetLocation);
	bool IntendRotate(FVector TargetLocation);

public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnLeft(float Throw);
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTracks(UTankTrack* ALeftTrack, UTankTrack* ARightTrack);

	virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;
	virtual bool RequestDirectRotate(const FVector & MoveVelocity, bool bForceMaxSpeed);
};
