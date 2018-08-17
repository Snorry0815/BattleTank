#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTower.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTower : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeSpeed);

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10.f;


protected:
	virtual void BeginPlay() override;
	
};
