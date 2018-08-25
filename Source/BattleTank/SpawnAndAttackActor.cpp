#include "SpawnAndAttachActor.h"
#include "Engine/World.h"

USpawnAndAttachActor::USpawnAndAttachActor()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpawnAndAttachActor::BeginPlay()
{
	Super::BeginPlay();

	if (ActorClassToSpawn)
	{
		auto* SpawnedActor = GetWorld()->SpawnActor(ActorClassToSpawn);
		if (!SpawnedActor)
			return;

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
		SpawnedActor->AttachToComponent(this, AttachmentRules);

		auto* Parent = SpawnedActor->GetAttachParentActor();

		if (Parent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Parent: %s"), *Parent->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Orphan"));
		}
	}
}