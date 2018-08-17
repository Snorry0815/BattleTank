// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(const FVector& AimLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(class UTankBarrel* BarrelToSet, const FName& BarrelSoccketNameToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTowerReference(class UTankTower* TowerToSet);

	UFUNCTION(BlueprintCallable, Category = Controls)
	void Fire();

protected:
	UPROPERTY(VisibleAnywhere)
	class UAimComponent* AimComp = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000;
};
