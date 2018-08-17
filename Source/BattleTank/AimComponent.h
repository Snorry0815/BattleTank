// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AimAt(const FVector& AimLocation, float LaunchSpeed);
	
	void SetBarrelReference(class UTankBarrel* BarrelToSet, const FName& BarrelSoccketNameToSet);
	void SetTowerReference(class UTankTower* TowerToSet);

protected:
	void MoveBarrelTowards(const FVector& AimDirection);
	void MoveTowerTowards(const FVector& AimDirection);

	// Called when the game starts
	virtual void BeginPlay() override;

	class UTankBarrel* Barrel;
	FName BarrelSocketName;

	class UTankTower* Tower;
};
