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

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(class UTankTower* TowerToSet, class UTankBarrel* BarrelToSet, const FName& BarrelSoccketNameToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AimAt(const FVector& AimLocation, float LaunchSpeed);

protected:
	void MoveBarrelTowards(const FVector& AimDirection);
	void MoveTowerTowards(const FVector& AimDirection);

	// Called when the game starts
	virtual void BeginPlay() override;

	class UTankBarrel* Barrel;
	FName BarrelSocketName;

	class UTankTower* Tower;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FringinState = EFiringState::Reloading;
};
