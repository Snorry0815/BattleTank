#include "Tank.h"
#include "AimComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	AimComp = CreateDefaultSubobject<UAimComponent>(FName("AimComp"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("TankMovementComponent"));
}

void ATank::AimAt(const FVector& AimLocation)
{
	AimComp->AimAt(AimLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet, const FName& BarrelSoccketNameToSet)
{
	Barrel = BarrelToSet;
	BarrelSocketName = BarrelSoccketNameToSet;

	AimComp->SetBarrelReference(BarrelToSet, BarrelSoccketNameToSet);
}

void ATank::SetTowerReference(UTankTower* TowerToSet)
{
	AimComp->SetTowerReference(TowerToSet);
}

void ATank::Fire()
{
	float timeSinceLastShoot = GetWorld()->GetTimeSeconds() - LastFireTime;
	if (timeSinceLastShoot < ReloadTimeInSeconds)
		return;

	if (!ProjectileClass)
		return;

	if (!Barrel)
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

void ATank::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = -ReloadTimeInSeconds;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATank::Fire);
}

