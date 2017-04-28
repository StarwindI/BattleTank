#pragma once

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

private:

protected:
	virtual void BeginPlay() override;
	UProjectileMovementComponent* ProjectileMovement = nullptr;

public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float Speed);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
