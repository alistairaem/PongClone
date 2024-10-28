#include "Paddle/CpuPaddle.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ACpuPaddle::ACpuPaddle()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(9.0f, 1.0f, 60.0f));
	RootComponent = BoxComponent;

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetBoxExtent(FVector(9.0f, 1.0f, 62.0f));
	OverlapComponent->SetupAttachment(RootComponent);

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	PaperSprite->SetupAttachment(RootComponent);
	TArray<AActor*> Balls;
	UGameplayStatics::GetAllActorsWithTag(this, FName("Ball"), Balls);

	if (Balls.Num() > 0)
	{
		Ball = Balls[0];
	}
}

void ACpuPaddle::BeginPlay()
{
	Super::BeginPlay();
}

void ACpuPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckBallPosition(DeltaTime);
}

void ACpuPaddle::MovePaddle(float Value, float DeltaTime)
{
	if (Value != 0.0f)
	{
		float PaddleYPosition = GetActorLocation().Y;
		if (Value > 0.0f && PaddleYPosition >= 122.0f)
		{
			return;
		}

		if (Value < 0.0f && PaddleYPosition <= -122.0f)
		{
			return;
		}

		FVector NewLocation = GetActorLocation() + FVector(0.0f, Value * PaddleSpeed * DeltaTime, 0.0f);
		SetActorLocation(NewLocation);
	}
}

void ACpuPaddle::CheckBallPosition(float DeltaTime)
{
	if (Ball == nullptr) return;

	float BallYLocation = Ball->GetActorLocation().Y;
	float PaddleYLocation = GetActorLocation().Y;

	float Threshold = 10.0f;

	if (FMath::Abs(BallYLocation - PaddleYLocation) > Threshold)
	{
		if (BallYLocation < PaddleYLocation)
		{
			MovePaddle(-1.0f, DeltaTime);
		}
		else if (BallYLocation > PaddleYLocation)
		{
			MovePaddle(1.0f, DeltaTime);
		}
	}
}
