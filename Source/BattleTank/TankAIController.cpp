#include "TankAIController.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto* ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController possesing : %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController not possesing a tank!"));
	}

	auto* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank : %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No player tank!"));
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto* AiTank = GetControlledTank();
	if (AiTank == nullptr)
		return;
	
	auto* PlayerTank = GetPlayerTank();
	if (PlayerTank == nullptr)
		return;

	AiTank->AimAt(PlayerTank->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
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
