#include "Tank.h"
#include "AimComponent.h"
#include "Components/InputComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	AimComp = CreateDefaultSubobject<UAimComponent>(FName("AimComp"));
}

void ATank::AimAt(const FVector& AimLocation)
{
	AimComp->AimAt(AimLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet, const FName& BarrelSoccketNameToSet)
{
	AimComp->SetBarrelReference(BarrelToSet, BarrelSoccketNameToSet);
}

void ATank::SetTowerReference(UTankTower* TowerToSet)
{
	AimComp->SetTowerReference(TowerToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATank::Fire);
}

