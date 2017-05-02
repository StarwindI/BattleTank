#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Ready,
	Empty
};

class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY() 

private:
	float FireTime;

protected:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = Setup)
		EFiringState FiringState = EFiringState::Reloading;

	bool MoveBarrelTowards(FVector AimDirection);

public:	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTime = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LounchSpeed = 8000.0f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float DistanceShot = 8000.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float DistanceLook = 200000.0f;
	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	bool Reloaded();
	bool DistanceAt(FVector HitLocation);
	bool AimAt(FVector HitLocation);
	EFiringState CheckState(bool is_elevated, bool is_reloaded);
	UFUNCTION(BlueprintCallable)
		void Fire();
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretBarrel(UTankTurret* ATurret, UTankBarrel* ABarrel);
	UFUNCTION(BlueprintCallable)
		int GetProjectileCount();
};
