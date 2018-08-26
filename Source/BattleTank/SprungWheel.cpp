// Copyright none Just a tutorial

#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Spring"));	
	SetRootComponent(Spring);

	Spring->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	Spring->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	Spring->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.f);

	Spring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Spring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Spring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);

	Spring->SetLinearPositionDrive(false, false, true);
	Spring->SetLinearVelocityDrive(false, false, true);
	Spring->SetLinearDriveParams(5000.f, 2000.f, 0.f);

	Axel = CreateDefaultSubobject<USphereComponent>(TEXT("Axel"));
	Axel->SetupAttachment(Spring);
	Axel->SetSimulatePhysics(true);

	AxelWheelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("AxelWheelConstrain"));
	AxelWheelConstrain->SetupAttachment(Axel);

	AxelWheelConstrain->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	AxelWheelConstrain->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	AxelWheelConstrain->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.f);

	AxelWheelConstrain->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	AxelWheelConstrain->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	AxelWheelConstrain->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0.f);

	Spring->SetLinearPositionDrive(false, false, true);
	Spring->SetLinearVelocityDrive(false, false, true);
	Spring->SetLinearDriveParams(5000.f, 2000.f, 0.f);

	Wheel = CreateDefaultSubobject<USphereComponent>(TEXT("Wheel"));
	Wheel->SetupAttachment(Axel);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}


// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstrained();
}

void ASprungWheel::SetupConstrained()
{
	auto* Parent = GetAttachParentActor();

	if (!Parent)
		return;

	auto* RootAsPrimitive = Cast<UPrimitiveComponent>(Parent->GetRootComponent());
	if (!RootAsPrimitive)
		return;

	Spring->SetConstrainedComponents(RootAsPrimitive, NAME_None, Axel, NAME_None);
	AxelWheelConstrain->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

