#include "TankPlayerController.h"
#include "AimComponent.h"
#include "Engine/World.h"

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto* PawnTank = GetPawn();
	if (!PawnTank)
		return;
	
	auto* AimComponent = PawnTank->FindComponentByClass<UAimComponent>();
	if (ensure(AimComponent))
		FoundAimingComponent(AimComponent);
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto* PawnTank = GetPawn();
	if (!PawnTank)
		return;

	FVector HitLocation;
	if (!GetAimLocation(HitLocation))
		return;

	auto* AimComponent = PawnTank->FindComponentByClass<UAimComponent>();
	if (ensure(AimComponent))
		AimComponent->AimAt(HitLocation);
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
	if (!ensure(World))
		return false;

	auto* PawnTank = GetPawn();
	if (!ensure(PawnTank))
		return false;

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