#include "BattleTank.h"
#include "Tank.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetContolledTank(false);
	EnemyTank = GetContolledTank(true);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsEnenmyTank();
}

ATank* ATankAIController::GetContolledTank(bool _player) 
{
	ATank* result;
	if (_player) {
		result = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()); 
	} else {
		result = Cast<ATank>(GetPawn());
	}
	if (result) {
		return result;
	} else {
		return nullptr;
	}
}
void ATankAIController::AimTowardsEnenmyTank()
{
	if (ControlledTank && EnemyTank) {
		FVector HitLocation = EnemyTank->GetActorLocation();
		UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		UTankMovementComponent* MovementComponent = ControlledTank->FindComponentByClass<UTankMovementComponent>();
		if (AimingComponent) {
			if (AimingComponent->DistanceAt(HitLocation)) {
				if (AimingComponent->AimAt(HitLocation)) {
					AimingComponent->Fire();
				}
				MovementComponent->RequestDirectRotate(EnemyTank->GetActorLocation() - ControlledTank->GetActorLocation(), false);
			} else {
//				MoveToActor(EnemyTank, ControlledTank->DistanceRange); // не работает
				AimingComponent->AimAt(HitLocation);
				MovementComponent->RequestDirectMove(EnemyTank->GetActorLocation() - ControlledTank->GetActorLocation(), false);
			}
		}
	}
}

