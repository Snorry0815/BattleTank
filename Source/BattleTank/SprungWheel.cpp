// Copyright none Just a tutorial

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Spring"));	
	SetRootComponent(Spring);

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mass"));
	Mass->SetupAttachment(Spring);


	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel"));
	Wheel->SetupAttachment(Spring);


	Spring->SetConstrainedComponents(Mass, NAME_None, Wheel, NAME_None);
	Spring->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	Spring->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	Spring->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.f);

	Spring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Spring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Spring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);

	Spring->SetLinearPositionDrive(false, false, true);
	Spring->SetLinearVelocityDrive(false, false, true);
	Spring->SetLinearDriveParams(5000.f, 2000.f, 0.f);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

