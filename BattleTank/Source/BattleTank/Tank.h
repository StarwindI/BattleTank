#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();
};
