#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Blueprintcallable)
	class ATank* GetControlledTank() const;

protected:
	void AimTowardsCrosshair();

	bool GetTargetDirectionData(FVector& WorldLocation, FVector& WorldDirection) const;
	bool GetLookVectorHitDirection(const FVector& WorldLocation, const FVector& RayTraceEnd, FVector& OutHitLocation) const;

	bool GetAimLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D RelativeCorsshairLocation = FVector2D(0.5f, 0.33f);

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 100000.f;
};
