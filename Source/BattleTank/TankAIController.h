// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

	class ATank* GetPlayerTank() const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float AcceptanceRadiusForMovementToActor = 3000.f;
};
