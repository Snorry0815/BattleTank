#include "TankAIController.h"
#include "AimComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto* AiTank = GetPawn();
	if (!ensure(AiTank))
		return;

	auto* PlayerActor = GetPlayerActor();
	if (!ensure(PlayerActor))
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
