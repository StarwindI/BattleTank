#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* ControlledTank;

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLoction, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
		ATank* GetContolledTank() const;
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
		void FoundAimingComponent(UTankAimingComponent* AimingComponentReference);

public:
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
		float DistanceLook = 200000.0f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
