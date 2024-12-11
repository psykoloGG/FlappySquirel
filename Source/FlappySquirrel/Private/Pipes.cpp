#include "Pipes.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "SquirrelCharacter.h"
#include "Components/BoxComponent.h"

APipes::APipes()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TopPipe = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TopPipe"));
	TopPipe->SetupAttachment(Root);

	BottomPipe = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BottomPipe"));
	BottomPipe->SetupAttachment(Root);

	TopPipeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TopPipeCollision"));
	TopPipeCollision->SetupAttachment(TopPipe);

	BottomPipeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomPipeCollision"));
	BottomPipeCollision->SetupAttachment(BottomPipe);

	ScoreCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ScoreCollision"));
	ScoreCollision->SetupAttachment(Root);

	ScoreCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	ScoreCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ScoreCollision->SetCollisionProfileName("OverlapAll");
	ScoreCollision->OnComponentBeginOverlap.AddDynamic(this, &APipes::OnScore);

	static ConstructorHelpers::FObjectFinder<UPaperSprite> PipeSprite(TEXT("/Script/Paper2D.PaperSprite'/Game/Sprites/pipe_Sprite.pipe_Sprite'"));
	if (PipeSprite.Succeeded())
	{
		TopPipe->SetSprite(PipeSprite.Object);
		TopPipe->SetRelativeRotation(FRotator(0.0f, 0.0f, 180.0f));
		TopPipe->SetRelativeLocation(FVector(0.0f, 0.0f, 800.0f));
		
		BottomPipe->SetSprite(PipeSprite.Object);
		BottomPipe->SetRelativeLocation(FVector(0.0f, 0.0f, -800.0f));
	}

	float RandHeight = FMath::RandRange(MinSpawnHeight, MaxSpawnHeight);
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, RandHeight));

	Tags.Add("Death");
}

void APipes::BeginPlay()
{
	Super::BeginPlay();
	
}

void APipes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + FVector(ApproachSpeed * DeltaTime, 0.0f, 0.0f));
}

void APipes::OnScore(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ASquirrelCharacter::StaticClass()))
	{
		ASquirrelCharacter* Squirrel = Cast<ASquirrelCharacter>(OtherActor);
		if (Squirrel)
		{
			Squirrel->AddScore();
		}
	}
}

