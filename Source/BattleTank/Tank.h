// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDied);

public:
	ATank();

	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHeahlthInPercent() const
	{
		if (MaxHealth == 0.f)
			return 0.f;

		return CurrentHealth / MaxHealth;
	}

	FTankDied TankDied;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth = 20.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth;

	bool bIsDead = false;
};
