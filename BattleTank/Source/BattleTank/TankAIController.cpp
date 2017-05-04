#include "BattleTank.h"
#include "Healthy.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetContolledTank(true);
	EnemyTank = GetContolledTank(false);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsEnenmyTank();
}

void ATankAIController::OnDeath() {
	DetachFromControllerPendingDestroy();
}

void ATankAIController::DetachFromControllerPendingDestroy() {

}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		AHealthy* PossessedHealthy = Cast<AHealthy>(InPawn);
		if (ensure(PossessedHealthy)) {
			PossessedHealthy->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnDeath);
		}
	}
}

APawn* ATankAIController::GetContolledTank(bool self) 
{
	APawn* result;
	if (self) {
		result = GetPawn();
	} else {
		result = GetWorld()->GetFirstPlayerController()->GetPawn();
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
				if (MovementComponent) {
					MovementComponent->RequestDirectRotate(EnemyTank->GetActorLocation() - ControlledTank->GetActorLocation(), false);
				}
			} else {
				AimingComponent->AimAt(HitLocation);
//				MoveToActor(EnemyTank, AimingComponent->DistanceShot);
				if (MovementComponent) {
					MovementComponent->RequestDirectMove(EnemyTank->GetActorLocation() - ControlledTank->GetActorLocation(), false);
				}
			}
		}
	}
}

