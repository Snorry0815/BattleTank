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

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(class UTankBarrel* BarrelToSet, const FName& BarrelSoccketNameToSet);

	UFUNCTION(BlueprintCallable, Category = "Controls")
	void Fire();

protected:
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<class AProjectile> ProjectileClass;

	class UTankBarrel* Barrel;
	FName BarrelSocketName;

	UPROPERTY(EditDefaultsOnly)
	float ReloadTimeInSeconds = 3.f;

	float LastFireTime;
};
