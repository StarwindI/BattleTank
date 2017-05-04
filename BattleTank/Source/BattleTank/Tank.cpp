#include "BattleTank.h"
#include "Tank.h"

ATank::ATank() {
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	int32 result = FMath::Clamp<int32>(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);
	CurrentHealth -= result;
//	UE_LOG(LogTemp, Warning, TEXT("%s: damage %i, current health remain %i"), *GetName(), result, CurrentHealth)
	return result;
}

float ATank::GetHealthPercent() const {
	return (float) CurrentHealth / (float) Health;
}
