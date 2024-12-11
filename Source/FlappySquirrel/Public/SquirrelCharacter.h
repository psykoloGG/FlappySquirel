#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "SquirrelCharacter.generated.h"

class UDeathWidget;
class UScoreWidget;
class UStrengthCalibrationWidget;
class UCharacterMovementComponent;

UCLASS()
class FLAPPYSQUIRREL_API ASquirrelCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ASquirrelCharacter();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	UFUNCTION()
	void AddScore();

	// This will get calibrated at the beginning of the game
	UPROPERTY(EditAnywhere)
	float MaxSquishingForce = 1024.0f;

	UPROPERTY(VisibleAnywhere)
	float CurrentSquishForce = 0.0f;

	// Depending on the Max squishing force this will be adjusted
	UPROPERTY(EditAnywhere)
	float ImpulseForcePercentage = 100.0f;

	// Impulse if maximum squishing force is applied
	UPROPERTY(EditAnywhere)
	float MaxImpulse = 10.0f;

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY()
	float TimeSinceLastSerialRead = 0.0f;

	UPROPERTY()
	int32 Score = 0;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// For testing purposes we need keyboard input
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere)
	class UInputAction* JumpAction;

	UPROPERTY()
	UStrengthCalibrationWidget* CalibrationWidget;

	UPROPERTY()
	UClass* StrengthCalibrationWidgetClass;

	UPROPERTY()
	UScoreWidget* ScoreWidget;

	UPROPERTY()
	UClass* ScoreWidgetClass;
	
	UPROPERTY()
	UDeathWidget* DeathWidget;

	UPROPERTY()
	UClass* DeathWidgetClass;
};
