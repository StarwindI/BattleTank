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

public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnLeft(float Throw);
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnRight(float Throw);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTracks(UTankTrack* ALeftTrack, UTankTrack* ARightTrack);
};
