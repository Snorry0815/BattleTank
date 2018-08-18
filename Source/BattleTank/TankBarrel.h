#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Events"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationInDegree = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationInDegree = 0.f;

protected:
	virtual void BeginPlay() override;
};
