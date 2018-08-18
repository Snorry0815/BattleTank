#include "TankAIController.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto* AiTank = Cast<ATank>(GetPawn());
	if (!ensure(AiTank))
		return;
	
	auto* PlayerTank = GetPlayerTank();
	if (!ensure(PlayerTank))
		return;

	MoveToActor(PlayerTank, AcceptanceRadiusForMovementToActor);
	AiTank->AimAt(PlayerTank->GetActorLocation());
	AiTank->Fire();
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto* World = GetWorld();
	if (!ensure(World))
		return nullptr;
	
	auto* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController))
		return nullptr;
	
	return Cast<ATank>(PlayerController->GetPawn());
}
