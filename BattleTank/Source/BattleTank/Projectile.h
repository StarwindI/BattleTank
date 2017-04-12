#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	UProjectileMovementComponent* ProjectileMovement = nullptr;

public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float Speed);
};
