#include "TankAIController.h"
#include "AimComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto* AiTank = GetPawn();
	if (!(AiTank))
		return;

	auto* PlayerActor = GetPlayerActor();
	if (!(PlayerActor))
		return;

	MoveToActor(PlayerActor, AcceptanceRadiusForMovementToActor);

	auto* AimComponent = AiTank->FindComponentByClass<UAimComponent>();
	if (!ensure(AimComponent))
		return;

	AimComponent->AimAt(PlayerActor->GetActorLocation());
	if (AimComponent->IsLockedOn())
		AimComponent->Fire();	
}

AActor* ATankAIController::GetPlayerActor() const
{
	auto* World = GetWorld();
	if (!ensure(World))
		return nullptr;
	
	auto* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController))
		return nullptr;
	
	return PlayerController->GetPawn();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	auto* pawnAsTank = Cast<ATank>(InPawn);
	if (pawnAsTank)
		pawnAsTank->TankDied.AddDynamic(this, &ATankAIController::TankDied);
}

void ATankAIController::TankDied()
{
	auto* CurrentPawn = GetPawn();
	if (CurrentPawn)
		CurrentPawn->DetachFromControllerPendingDestroy();
}
