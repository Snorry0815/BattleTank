#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnAndAttachActor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnAndAttachActor : public USceneComponent
{
	GENERATED_BODY()

public:	
	USpawnAndAttachActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Suspension")
	TSubclassOf<AActor> ActorClassToSpawn;
};
