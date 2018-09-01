// Copyright none Just a tutorial

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	ASprungWheel();
	void SetupConstrained();

	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(class UPrimitiveComponent* HitComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyDrivingForce();

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPhysicsConstraintComponent* Spring = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USphereComponent* Axel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPhysicsConstraintComponent* AxelWheelConstrain = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USphereComponent* Wheel = nullptr;

	float CurrentForceMagnitude;
};
