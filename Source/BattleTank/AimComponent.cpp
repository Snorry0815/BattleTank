// Fill out your copyright notice in the Description page of Project Settings.

#include "AimComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTower.h"

// Sets default values for this component's properties
UAimComponent::UAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAimComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UAimComponent::AimAt(const FVector& AimLocation, float LaunchSpeed)
{
	if (!Barrel)
		return;

	const auto StartLocation = Barrel->GetSocketLocation(BarrelSocketName);
	FVector TossVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, TossVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		auto AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTowerTowards(AimDirection);
	}
}

void UAimComponent::SetBarrelReference(UTankBarrel* BarrelToSet, const FName& BarrelSoccketNameToSet)
{
	Barrel = BarrelToSet;
	BarrelSocketName = BarrelSoccketNameToSet;
}

void UAimComponent::SetTowerReference(UTankTower* TowerToSet)
{
	Tower = TowerToSet;
}

void UAimComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	if (!Barrel)
		return;
	

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UAimComponent::MoveTowerTowards(const FVector& AimDirection)
{
	if (!Tower)
	{
		UE_LOG(LogActor, Error, TEXT("Tower not Setup for aimcomponent in %s!"), *GetOwner()->GetName());
		return;
	}

	auto BarrelRotator = Tower->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	float OpositeYaw = DeltaRotator.Yaw > 0.f ? DeltaRotator.Yaw - 360.f : 360 + DeltaRotator.Yaw;

	Tower->Rotate(FMath::Abs(DeltaRotator.Yaw) < FMath::Abs(OpositeYaw) ? DeltaRotator.Yaw : OpositeYaw);
}
