#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeSpawner.generated.h"

UCLASS()
class FLAPPYSQUIRREL_API APipeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	APipeSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float PipeSpeed = 300.0f;
	
	// The delay between spawning pipes in seconds
	UPROPERTY(EditAnywhere)
	float PipeSpawnDelay = 2.0f;

	UPROPERTY(EditAnywhere)
	float PipeSpeedupIncrement = 15.0f;

	UPROPERTY(EditAnywhere)
	float PipeSpawnRateIncrement = 0.1f;

	// The rate at which the difficulty increases in seconds
	UPROPERTY(EditAnywhere)
	float IncreaseDifficultyTimeEvery = 10.0f;

	UPROPERTY()
	float TimeSinceLastPipeSpawn = 2.0f;

	UPROPERTY()
	float TimeSinceLastDifficultyIncrease = 0.0f;

	UPROPERTY(EditAnywhere)
	bool bGameStarted = false;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
};
