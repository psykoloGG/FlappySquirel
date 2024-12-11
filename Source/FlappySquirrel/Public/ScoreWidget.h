#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYSQUIRREL_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(bindWidget))
	class UTextBlock* ScoreText;
};
