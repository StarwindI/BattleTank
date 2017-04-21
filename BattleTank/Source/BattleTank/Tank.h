#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UTankBarrel* Barrel = nullptr;
	float FireTime;

protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent = nullptr;

public:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTime = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LounchSpeed = 8000.0f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float DistanceRange = 30000.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	ATank();
	virtual void BeginPlay() override;
	FVector GetBarrelStartLocation() const;
	bool AimAt(FVector HitLocation) const;
	void SetTurret(UTankTurret* ATurret);
	void SetBarrel(UTankBarrel* ABarrel);
	void MoveTo(AActor* Goal, float AcceptanceRadius);
	bool RotateTo(AActor* Goal);
	UFUNCTION(BlueprintCallable)
		void Fire();
};
