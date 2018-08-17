#include "TankTower.h"
#include "Engine/World.h"


void UTankTower::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	const auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	const auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(RelativeRotation.Pitch, RawNewRotation, RelativeRotation.Roll));
}

void UTankTower::BeginPlay()
{
	Super::BeginPlay();

	IgnoreActorWhenMoving(GetOwner(), true);
}
