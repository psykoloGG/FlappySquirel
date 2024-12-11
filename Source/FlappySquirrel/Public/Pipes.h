#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "GameFramework/Actor.h"
#include "Pipes.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class FLAPPYSQUIRREL_API APipes : public AActor
{
	GENERATED_BODY()
	
public:
	APipes();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SendThem(float Speed);
private:
	UFUNCTION()
	void OnScore(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY()
	UPaperSpriteComponent* TopPipe;

	UPROPERTY()
	UPaperSpriteComponent* BottomPipe;

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY()
	UBoxComponent* TopPipeCollision;

	UPROPERTY()
	UBoxComponent* BottomPipeCollision;

	UPROPERTY()
	UBoxComponent* ScoreCollision;

	UPROPERTY()
	float ApproachSpeed;
	
	UPROPERTY()
	float MinSpawnHeight = 400.0f;

	UPROPERTY()
	float MaxSpawnHeight = 900.0f;
};

inline void APipes::SendThem(float Speed)
{
	this->ApproachSpeed = Speed;
}
