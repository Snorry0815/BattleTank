#include "TankMovementComponent.h"
#include "Engine/World.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: %s intend move forward Throw %f"), Time, *GetName(), Throw);
}
