#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	RootComponent = CollisionMesh;
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	LaunchBlast->SetupAttachment(CollisionMesh);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	ImpactBlast->SetupAttachment(CollisionMesh);
	ImpactBlast->bAutoActivate = false;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComp"));
	MovementComp->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
}

void AProjectile::LaunchProjectile(float Speed)
{
	MovementComp->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComp->Activate();
}

