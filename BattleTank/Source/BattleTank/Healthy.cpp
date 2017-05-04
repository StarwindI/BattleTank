#include "BattleTank.h"
#include "Healthy.h"


AHealthy::AHealthy()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHealthy::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = Health;
}

float AHealthy::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	if (CurrentHealth > 0) {
		int32 result = FMath::Clamp<int32>(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);
		CurrentHealth -= result;
		if (CurrentHealth <= 0) {
			OnDeath.Broadcast();
		}
		return result;
	}
	else {
		return 0;
	}
}

float AHealthy::GetHealthPercent() const {
//	UE_LOG(LogTemp, Warning, TEXT("%s: Current health %i"), *GetName(), CurrentHealth)
	return (float)CurrentHealth / (float)Health;
}

FLinearColor AHealthy::GetHealthColor() const {
	float health = GetHealthPercent();
	if (health >= 0.7) {
		return FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);
	} else 
	if (health >= 0.3) {
		return FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
	}
	else {
		return FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
}
