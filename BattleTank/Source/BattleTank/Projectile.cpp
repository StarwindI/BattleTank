#include "BattleTank.h"
#include "Projectile.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	ProjectileMovement->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate(true);
}
