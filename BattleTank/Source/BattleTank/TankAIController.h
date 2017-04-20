#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	ATank* ControlledTank;
	ATank* EnemyTank;
	ATank* GetContolledTank(bool _player);

	void AimTowardsEnenmyTank();
//	bool GetLookVectorHitLocation(AActor* Goal);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
