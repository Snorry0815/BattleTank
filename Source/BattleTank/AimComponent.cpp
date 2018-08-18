#include "AimComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTower.h"
#include "Engine/World.h"
#include "Projectile.h"

UAimComponent::UAimComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAimComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = -ReloadTimeInSeconds;
}

void UAimComponent::Initialise(UTankTower* TowerToSet, UTankBarrel* BarrelToSet, const FName& BarrelSoccketNameToSet)
{
	Barrel = BarrelToSet;
	BarrelSocketName = BarrelSoccketNameToSet;
	Tower = TowerToSet;
}

void UAimComponent::AimAt(const FVector& AimLocation)
{
	if (!ensure(Barrel))
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

void UAimComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	if (!ensure(Barrel))
		return;
	

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UAimComponent::MoveTowerTowards(const FVector& AimDirection)
{
	if (!ensure(Tower))
		return;

	auto BarrelRotator = Tower->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	float OpositeYaw = DeltaRotator.Yaw > 0.f ? DeltaRotator.Yaw - 360.f : 360 + DeltaRotator.Yaw;

	Tower->Rotate(FMath::Abs(DeltaRotator.Yaw) < FMath::Abs(OpositeYaw) ? DeltaRotator.Yaw : OpositeYaw);
}

void UAimComponent::Fire()
{
	float timeSinceLastShoot = GetWorld()->GetTimeSeconds() - LastFireTime;
	if (timeSinceLastShoot < ReloadTimeInSeconds)
		return;

	if (!ensure(ProjectileClass))
		return;

	if (!ensure(Barrel))
		return;

	LastFireTime = GetWorld()->GetTimeSeconds();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = Cast<APawn>(GetOwner());
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const auto StartLocation = Barrel->GetSocketLocation(BarrelSocketName);
	const auto StartRotation = Barrel->GetSocketRotation(BarrelSocketName);

	auto* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, StartLocation, StartRotation, SpawnParameters);
	auto* RootAsPrimitive = Cast<UPrimitiveComponent>(Projectile->GetRootComponent());
	RootAsPrimitive->IgnoreActorWhenMoving(GetOwner(), true);
	Barrel->IgnoreActorWhenMoving(Projectile, true);

	Projectile->LaunchProjectile(LaunchSpeed);
}
