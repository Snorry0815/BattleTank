// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto* ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player possesing : %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player not possesing a tank!"));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto* PawnTank = GetControlledTank();
	if (PawnTank == nullptr)
		return;

	FVector HitLocation;
	if (!GetAimLocation(HitLocation))
		return;

	PawnTank->AimAt(HitLocation);
}

bool ATankPlayerController::GetAimLocation(FVector& OutHitLocation) const
{
	FVector WorldLocation;
	FVector WorldDirection;
	if (!GetTargetDirectionData(WorldLocation, WorldDirection))
		return false;

	const FVector RayTraceEnd = WorldLocation + WorldDirection * LineTraceRange;

	if (!GetLookVectorHitDirection(WorldLocation, RayTraceEnd, OutHitLocation))
		return false;

	return true;
}

bool ATankPlayerController::GetTargetDirectionData(FVector& WorldLocation, FVector& WorldDirection) const
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	const FVector2D ScreenLocation(RelativeCorsshairLocation.X * ViewportSizeX, RelativeCorsshairLocation.Y * ViewportSizeY);
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
}

bool ATankPlayerController::GetLookVectorHitDirection(const FVector& WorldLocation, const FVector& RayTraceEnd, FVector& OutHitLocation) const
{
	auto* World = GetWorld();
	if (World == nullptr)
	{
		return false;
	}

	auto* PawnTank = GetControlledTank();
	if (PawnTank == nullptr)
	{
		return false;
	}

	FHitResult OutHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(PawnTank);

	FCollisionResponseParams ResponseParams;
	if (World->LineTraceSingleByChannel(OutHit, WorldLocation, RayTraceEnd, ECollisionChannel::ECC_Visibility, QueryParams, ResponseParams))
	{
		OutHitLocation = OutHit.ImpactPoint;
	}
	else
	{
		OutHitLocation = RayTraceEnd;
	}

	return true;
}