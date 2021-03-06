#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/*
 * TankTrack is used to set maximum driving force, 
 * and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Events"))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

protected:
	void DriveTrack(float CurrentThrottle);
	TArray<class ASprungWheel*> GetWheels() const;

	// Max force per track, in Newtons 
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.f;
};
