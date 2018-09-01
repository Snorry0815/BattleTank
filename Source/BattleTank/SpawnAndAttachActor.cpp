#include "SpawnAndAttachActor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

USpawnAndAttachActor::USpawnAndAttachActor()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpawnAndAttachActor::BeginPlay()
{
	Super::BeginPlay();

	if (ActorClassToSpawn)
	{
		SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(ActorClassToSpawn, GetComponentTransform(), GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if (!SpawnedActor)
			return;

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
		SpawnedActor->AttachToComponent(this, AttachmentRules);
		UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
	}
}