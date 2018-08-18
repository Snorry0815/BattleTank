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
	PrimaryComponentTick.bCanEverTick = true;
}

void UAimComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
	FiringinState = EFiringState::Reloading;
}

void UAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if ((FiringinState == EFiringState::Reloading) && ((GetWorld()->GetTimeSeconds() - LastFireTime) >= ReloadTimeInSeconds))
		FiringinState = EFiringState::Aiming;
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
		MoveBarrelAndTowerTowards(AimDirection);
	}
}

void UAimComponent::MoveBarrelAndTowerTowards(const FVector& AimDirection)
{
	if (!ensure(Barrel))
		return;

	if (!ensure(Tower))
		return;

	FVector BarrelForwardVector = Barrel->GetForwardVector();
	if (AimDirection.Equals(BarrelForwardVector, 0.01f))
	{
		if (FiringinState == EFiringState::Aiming)
			FiringinState = EFiringState::Locked;
	}
	else
	{
		if (FiringinState == EFiringState::Locked)
			FiringinState = EFiringState::Aiming;
	}

	auto BarrelRotator = BarrelForwardVector.Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto BarrelDeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(BarrelDeltaRotator.Pitch);

	auto TowerRotator = Tower->GetForwardVector().Rotation();
	auto DeltaTowerRotator = AimAsRotator - BarrelRotator;
	float OpositeYaw = DeltaTowerRotator.Yaw > 0.f ? DeltaTowerRotator.Yaw - 360.f : 360 + DeltaTowerRotator.Yaw;

	Tower->Rotate(FMath::Abs(DeltaTowerRotator.Yaw) < FMath::Abs(OpositeYaw) ? DeltaTowerRotator.Yaw : OpositeYaw);
}

void UAimComponent::Fire()
{
	if (FiringinState == EFiringState::Reloading)
		return;

	if (!ensure(ProjectileClass))
		return;

	if (!ensure(Barrel))
		return;

	LastFireTime = GetWorld()->GetTimeSeconds();
	FiringinState = EFiringState::Reloading;

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
