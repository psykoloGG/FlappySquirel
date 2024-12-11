#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StrengthCalibrationWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class FLAPPYSQUIRREL_API UStrengthCalibrationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CalibrationTimeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CalibrationStrengthText;

	UPROPERTY()
	float MaxSquishForce = 0.0f;

	UPROPERTY()
	float SquishCalibrationTime = 5.0f;

	UPROPERTY()
	float SquishCalibrationTimePassed = 0.0f;

	UPROPERTY()
	bool bIsCalibrated = false;
};
