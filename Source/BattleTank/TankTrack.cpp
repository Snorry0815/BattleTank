#include "TankTrack.h"
#include "Engine/World.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySidewaysForce();
	DriveTrack();
}

void UTankTrack::ApplySidewaysForce()
{
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto* Owner = GetOwner();
	auto SlippageSpeed = FVector::DotProduct(Owner->GetActorRightVector(), Owner->GetVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto* RootAsPrimitive = Cast<UPrimitiveComponent>(Owner->GetRootComponent());
	auto CorrectionForce = (RootAsPrimitive->GetMass() * CorrectionAcceleration / 2.f);
	RootAsPrimitive->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	CurrentThrottle = 0.f;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp(CurrentThrottle + Throttle, -1.f, 1.f);
}
