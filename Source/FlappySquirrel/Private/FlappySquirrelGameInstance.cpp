#include "FlappySquirrelGameInstance.h"

bool UFlappySquirrelGameInstance::GetCurrentSquishForce(float& Value)
{
	bool bSuccessfulFloatRead = false;

	if (!SerialCom)
	{
		return false;
	}
	
	FString SquishForce = SerialCom->Readln(bSuccessfulFloatRead);
	if (bSuccessfulFloatRead)
	{
		if (SquishForce.IsNumeric())
		{
			Value = FCString::Atof(*SquishForce);
			return true;
		}
		return false;
	}
	return false;
}

void UFlappySquirrelGameInstance::Init()
{
	Super::Init();
	SerialCom = USerialCom::OpenComPort(bIsComPortOpened, 4, 9600);
}

void UFlappySquirrelGameInstance::Shutdown()
{
	Super::Shutdown();
	if (SerialCom)
	{
		SerialCom->Close();
	}
}
