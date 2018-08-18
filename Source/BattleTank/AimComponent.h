// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(class UTankTower* TowerToSet, class UTankBarrel* BarrelToSet, const FName& BarrelSoccketNameToSet);

	void AimAt(const FVector& AimLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	void MoveBarrelAndTowerTowards(const FVector& AimDirection);

	class UTankBarrel* Barrel;
	FName BarrelSocketName;

	class UTankTower* Tower;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringinState = EFiringState::Reloading;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000; 

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	float ReloadTimeInSeconds = 3.f;

	float LastFireTime;
};
