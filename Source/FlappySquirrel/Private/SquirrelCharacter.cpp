#include "SquirrelCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FlappySquirrelGameInstance.h"
#include "ScoreWidget.h"
#include "StrengthCalibrationWidget.h"
#include "DeathWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextBlock.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASquirrelCharacter::ASquirrelCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UStrengthCalibrationWidget> StrengthCalibrationWidgetClassFinder(TEXT("/Game/WBP_StrengthCalibration"));
	if (StrengthCalibrationWidgetClassFinder.Succeeded())
	{
		StrengthCalibrationWidgetClass = StrengthCalibrationWidgetClassFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UScoreWidget> ScoreWidgetClassFinder(TEXT("/Game/WBP_Score"));
	if (ScoreWidgetClassFinder.Succeeded())
	{
		ScoreWidgetClass = ScoreWidgetClassFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UDeathWidget> DeathWidgetClassFinder(TEXT("/Game/WBP_Death"));
	if (DeathWidgetClassFinder.Succeeded())
	{
		DeathWidgetClass = DeathWidgetClassFinder.Class;
	}
}

void ASquirrelCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ASquirrelCharacter::OnHit);
	GetCharacterMovement()->GroundFriction = 0.0f;
	GetCharacterMovement()->GravityScale = 0.0f;
	
	if (!ScoreWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ScoreWidgetClass is null"));
		return;
	}
	ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
	ScoreWidget->ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
	ScoreWidget->AddToViewport();

	if (!StrengthCalibrationWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("StrengthCalibrationWidgetClass is null"));
		return;
	}
	CalibrationWidget = CreateWidget<UStrengthCalibrationWidget>(GetWorld(), StrengthCalibrationWidgetClass);
	CalibrationWidget->AddToViewport();

}

void ASquirrelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CalibrationWidget)
	{
		if (CalibrationWidget->bIsCalibrated)
		{
			UFlappySquirrelGameInstance* GameInstance = Cast<UFlappySquirrelGameInstance>(GetGameInstance());
			GameInstance->bGameCanStart = true;
			CalibrationWidget->RemoveFromParent();
			MaxSquishingForce = CalibrationWidget->MaxSquishForce;
			GetCharacterMovement()->GravityScale = 2.0f;
		}
		else
		{
			return;
		}
	}

	UFlappySquirrelGameInstance* GameInstance = Cast<UFlappySquirrelGameInstance>(GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is null"));
		return;
	}

	if (!GameInstance->GetCurrentSquishForce(CurrentSquishForce))
	{
		return;
	}
	
	if (CurrentSquishForce > MaxSquishingForce)
	{
		CurrentSquishForce = MaxSquishingForce;
	}
	ImpulseForcePercentage = CurrentSquishForce / MaxSquishingForce * 100.0f;
	if (ImpulseForcePercentage == 0.0f)
	{
		return;
	}

	Jump();
}

void ASquirrelCharacter::Jump()
{
	GetCharacterMovement()->Velocity.Z = 0.0f;
	GetCharacterMovement()->AddImpulse(FVector(0.0f, 0.0f, MaxImpulse * ImpulseForcePercentage), true);
}

void ASquirrelCharacter::AddScore()
{
	Score += 1;
	ScoreWidget->ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
}

void ASquirrelCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Death"))
	{
		CreateWidget(GetWorld(), DeathWidgetClass)->AddToViewport();
	}
	// stop the other parts of the game, but for demo left as is
}

void ASquirrelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASquirrelCharacter::Jump);
}

