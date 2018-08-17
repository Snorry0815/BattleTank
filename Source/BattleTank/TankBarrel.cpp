// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	const auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	const auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	
	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinElevationInDegree, MaxElevationInDegree), RelativeRotation.Yaw, RelativeRotation.Roll));
}

void UTankBarrel::BeginPlay()
{
	Super::BeginPlay();

	IgnoreActorWhenMoving(GetOwner(), true);
}
