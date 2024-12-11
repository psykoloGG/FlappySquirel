#include "PipeSpawner.h"

#include "EngineUtils.h"
#include "FlappySquirrelGameInstance.h"
#include "Pipes.h"

APipeSpawner::APipeSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void APipeSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void APipeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bGameStarted)
	{
		UFlappySquirrelGameInstance* GameInstance = Cast<UFlappySquirrelGameInstance>(GetGameInstance());
		if (!GameInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("GameInstance is null"));
			return;
		}

		if (!GameInstance->bGameCanStart)
		{
			return;
		}

		bGameStarted = true;
		return;
	}
	
	TimeSinceLastDifficultyIncrease += DeltaTime;
	TimeSinceLastPipeSpawn += DeltaTime;
	
	if (TimeSinceLastPipeSpawn >= PipeSpawnDelay)
	{
		FVector Location = GetActorLocation();
		Location.Z = 0.0f;
		APipes* Pipes = GetWorld()->SpawnActor<APipes>(APipes::StaticClass(), Location, FRotator::ZeroRotator);
		Pipes->SendThem(PipeSpeed);
		
		if (TimeSinceLastDifficultyIncrease >= IncreaseDifficultyTimeEvery)
		{
			PipeSpeed += PipeSpeedupIncrement;
			PipeSpawnDelay -= PipeSpawnRateIncrement;
			TimeSinceLastDifficultyIncrease = 0.0f;

			for (TActorIterator<APipes> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ActorItr->SendThem(PipeSpeed);
			}
		}
		TimeSinceLastPipeSpawn = 0.0f;
	}

}

