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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FVector GetBarrelStartLocation() const;
	bool AimAt(FVector HitLocation) const;
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret* ATurret);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* ABarrel);
	UFUNCTION(BlueprintCallable)
	void Fire();
	void MoveTo(AActor* Goal, float AcceptanceRadius);
};
