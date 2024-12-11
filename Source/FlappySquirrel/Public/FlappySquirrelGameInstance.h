#pragma once

#include "CoreMinimal.h"
#include "SerialCom.h"
#include "Engine/GameInstance.h"
#include "FlappySquirrelGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYSQUIRREL_API UFlappySquirrelGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION()
	bool GetCurrentSquishForce(float& Value);
	
	UPROPERTY()
	USerialCom* SerialCom;

	UPROPERTY()
	bool bIsComPortOpened = false;

	UPROPERTY()
	bool bGameCanStart = false;
	
private:
	virtual void Init() override;
	virtual void Shutdown() override;
};
