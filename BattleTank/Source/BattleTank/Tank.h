#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UTankBarrel* Barrel = nullptr;
	float NextFireTime = FPlatformTime::Seconds();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

public:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTime = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LounchSpeed = 8000.0f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float DistanceRange = 100000.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	ATank();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FVector GetBarrelStartLocation() const;
	void MoveTo(FVector HitLocation) const;
	bool AimAt(FVector HitLocation) const;
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurret(UTankTurret* ATurret);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrel(UTankBarrel* ABarrel);
	UFUNCTION(BlueprintCallable)
		void Fire();
};
