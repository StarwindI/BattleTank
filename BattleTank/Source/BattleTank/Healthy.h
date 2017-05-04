#pragma once

#include "GameFramework/Pawn.h"
#include "Healthy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthyDelegate);

UCLASS()
class BATTLETANK_API AHealthy : public APawn
{
	GENERATED_BODY()

private:
		UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 Health = 1000;
	int32 CurrentHealth;


protected:
	virtual void BeginPlay() override;

public:	
	AHealthy();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
		UFUNCTION(BlueprintPure, Category = Setup)
	float GetHealthPercent() const;
		UFUNCTION(BlueprintPure, Category = Setup)
	FLinearColor GetHealthColor() const;

	FHealthyDelegate OnDeath;

};
