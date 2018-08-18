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

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

protected:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	void ApplySidewaysForce();
	void DriveTrack();

	// Max force per track, in Newtons 
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.f;

	float CurrentThrottle = 0.f;
};
