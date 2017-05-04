#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
		UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 Health = 1000;
	int32 CurrentHealth = Health;
	ATank();

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
		UFUNCTION(BlueprintPure, Category = Setup)
	float GetHealthPercent() const;

};
