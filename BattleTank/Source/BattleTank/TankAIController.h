#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	APawn* ControlledTank;
	APawn* EnemyTank;
	APawn* GetContolledTank(bool self);
	void AimTowardsEnenmyTank();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
