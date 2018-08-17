#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Blueprintcallable)
	class ATank* GetControlledTank() const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void AimTowardsCrosshair();

	bool GetTargetDirectionData(FVector& WorldLocation, FVector& WorldDirection) const;
	bool GetLookVectorHitDirection(const FVector& WorldLocation, const FVector& RayTraceEnd, FVector& OutHitLocation) const;

	bool GetAimLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D RelativeCorsshairLocation = FVector2D(0.5f, 0.33f);

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 100000.f;
};
