#include "StrengthCalibrationWidget.h"

#include "FlappySquirrelGameInstance.h"
#include "Components/TextBlock.h"

void UStrengthCalibrationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsCalibrated)
	{
		return;
	}
	
	SquishCalibrationTimePassed += InDeltaTime;

	if (SquishCalibrationTimePassed >= SquishCalibrationTime)
	{
		// Calibration done
		bIsCalibrated = true;
	}
	UFlappySquirrelGameInstance* GameInstance = Cast<UFlappySquirrelGameInstance>(GetGameInstance());
	
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is null"));
		return;
	}

	float CurrentSquishForce = 0.0f;
	if (GameInstance->GetCurrentSquishForce(CurrentSquishForce))
	{
		if (CurrentSquishForce > MaxSquishForce)
		{
			MaxSquishForce = CurrentSquishForce;
			CalibrationStrengthText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *FString::SanitizeFloat(MaxSquishForce, 2))));
		}
	}

	CalibrationTimeText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *FString::SanitizeFloat(SquishCalibrationTime - SquishCalibrationTimePassed, 2))));
}
