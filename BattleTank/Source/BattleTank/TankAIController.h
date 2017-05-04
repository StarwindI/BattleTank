#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
		UFUNCTION()
	void OnDeath();
	APawn* ControlledTank;
	APawn* EnemyTank;
	APawn* GetContolledTank(bool self);
	void AimTowardsEnenmyTank();
	void DetachFromControllerPendingDestroy();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
};
