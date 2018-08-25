#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnAndAttackActor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnAndAttackActor : public USceneComponent
{
	GENERATED_BODY()

public:	
	USpawnAndAttackActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Suspension")
	TSubclassOf<AActor> ActorClassToSpawn;
};
