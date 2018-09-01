#include "TankTrack.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "SpawnAndAttachActor.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp(Throttle, -1.f, 1.f);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	if (Wheels.Num() == 0)
		return;

	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (auto* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Result;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	for (auto* Child : Children)
	{
		auto* ChildAsSpawner = Cast<USpawnAndAttachActor>(Child);
		if (!ChildAsSpawner)
			continue;
		auto* SprungWheel = Cast<ASprungWheel>(ChildAsSpawner->GetSpawnedActor());
		if (!SprungWheel)
			continue;

		if (!Result.Contains(SprungWheel))
			Result.Add(SprungWheel);
	}

	return Result;
}
