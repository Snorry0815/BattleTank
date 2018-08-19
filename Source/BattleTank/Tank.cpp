#include "Tank.h"
#include "Engine/World.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float LeftOverDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Max(0.f, CurrentHealth - LeftOverDamage);

	float AppliedDamage = OldHealth - CurrentHealth;

	UE_LOG(LogTemp, Warning, TEXT("Health left: %f after apllyingDamage of %f "), CurrentHealth, AppliedDamage);
	return AppliedDamage;
}
