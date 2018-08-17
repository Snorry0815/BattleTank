#include "TankAIController.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto* AiTank = Cast<ATank>(GetPawn());
	if (AiTank == nullptr)
		return;
	
	auto* PlayerTank = GetPlayerTank();
	if (PlayerTank == nullptr)
		return;

	AiTank->AimAt(PlayerTank->GetActorLocation());
	AiTank->Fire();
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto* World = GetWorld();
	if (World == nullptr)
		return nullptr;
	
	auto* PlayerController = World->GetFirstPlayerController();
	if (PlayerController == nullptr)
		return nullptr;
	
	return Cast<ATank>(PlayerController->GetPawn());
}
