#include "GameMode/PlayerCpuGameMode.h"
#include "Paddle/PlayerPaddle.h"
#include "Paddle/CpuPaddle.h"
#include "Ball/Ball.h"
#include "Ball/Goal.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"

APlayerCpuGameMode::APlayerCpuGameMode()
{
	DefaultPawnClass = nullptr;
	SpawnedBall = nullptr;
	BallSpawnPoint = nullptr;
	ScoreWidgetInstance = nullptr;
}

void APlayerCpuGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (BallClass != nullptr)
	{
		SpawnBall();
	}
	if (PlayerPaddleClass != nullptr && CpuPaddleClass != nullptr)
	{
		SpawnPaddles();
	}
	if (GoalClass != nullptr)
	{
		SpawnGoal("P1GoalSpawn", Player1Tag);
		SpawnGoal("P2GoalSpawn", CpuTag);
	}

	TArray<AActor*> UiComponents;
	UGameplayStatics::GetAllActorsWithTag(this, "ScoreUI", UiComponents);
	if (UiComponents.Num() > 0)
	{
		const AActor* ScoreActor = UiComponents[0];
		ScoreWidgetInstance = ScoreActor->FindComponentByClass<UWidgetComponent>();
	}
}

void APlayerCpuGameMode::SpawnPaddle(const TSubclassOf<AActor>& PaddleClass, const FName& SpawnTag,
                                     int32 PlayerControllerIndex = -1) const
{
	TArray<AActor*> SpawnPoints;
	UGameplayStatics::GetAllActorsWithTag(this, SpawnTag, SpawnPoints);

	if (SpawnPoints.Num() > 0 && PaddleClass)
	{
		const AActor* SpawnPoint = SpawnPoints[0];
		const FVector SpawnLocation = SpawnPoint->GetActorLocation();
		const FRotator SpawnRotation = SpawnPoint->GetActorRotation();

		if (AActor* SpawnedPaddle = GetWorld()->SpawnActor<AActor>(PaddleClass, SpawnLocation, SpawnRotation);
			PlayerControllerIndex >= 0 && SpawnedPaddle)
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(
				UGameplayStatics::GetPlayerController(GetWorld(), PlayerControllerIndex)))
			{
				PlayerController->Possess(Cast<APawn>(SpawnedPaddle));
			}
		}
	}
}

void APlayerCpuGameMode::SpawnGoal(const FString& SpawnTag, const FString& PlayerTag) const
{
	TArray<AActor*> SpawnPoints;
	UGameplayStatics::GetAllActorsWithTag(this, FName(SpawnTag), SpawnPoints);

	if (SpawnPoints.Num() > 0)
	{
		const AActor* SpawnPoint = SpawnPoints[0];
		const FVector SpawnLocation = SpawnPoint->GetActorLocation();
		const FRotator SpawnRotation = SpawnPoint->GetActorRotation();
		const AActor* goal = GetWorld()->SpawnActor<AActor>(GoalClass, SpawnLocation, SpawnRotation);
		if (UBoxComponent* goalBox = Cast<UBoxComponent>(goal->GetComponentByClass(UBoxComponent::StaticClass())))
		{
			goalBox->ComponentTags.Add(FName(PlayerTag));
		}
	}
}

void APlayerCpuGameMode::HandleGoalScored(const FString& GoalTag)
{
	if (GoalTag == Player1Tag)
	{
		++CpuScore;
	}
	else if (GoalTag == CpuTag)
	{
		++PlayerScore;
	}

	UpdateScore();
	ResetGame();
}

void APlayerCpuGameMode::SpawnPaddles() const
{
	SpawnPaddle(PlayerPaddleClass, FName("LeftPaddleSpawn"), 0);
	SpawnPaddle(CpuPaddleClass, FName("RightPaddleSpawn"));
}

void APlayerCpuGameMode::SpawnBall()
{
	TArray<AActor*> SpawnPoints;
	UGameplayStatics::GetAllActorsWithTag(this, FName("BallSpawn"), SpawnPoints);
	TSubclassOf<AActor> BallActorClass = BallClass;
	if (SpawnPoints.Num() > 0 && BallActorClass)
	{
		BallSpawnPoint = SpawnPoints[0];
		FVector SpawnLocation = BallSpawnPoint->GetActorLocation();
		const FRotator SpawnRotation = BallSpawnPoint->GetActorRotation();
		SpawnLocation.Z += 50.0f;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(BallActorClass, SpawnLocation, SpawnRotation);
		SpawnedBall = Cast<ABall>(SpawnedActor);
		SpawnedBall->ResetBall();
	}
}

void APlayerCpuGameMode::ResetGame() const
{
	if (SpawnedBall)
	{
		SpawnedBall->GetActorLocation() = BallSpawnPoint->GetActorLocation();
		SpawnedBall->GetActorRotation() = BallSpawnPoint->GetActorRotation();
		SpawnedBall->ResetBall();
	}
}

void APlayerCpuGameMode::UpdateScore() const
{
	if (ScoreWidgetInstance)
	{
		UUserWidget* MyScoreWidget = Cast<UUserWidget>(ScoreWidgetInstance->GetUserWidgetObject());

		UTextBlock* PlayerTextBlock = Cast<UTextBlock>(MyScoreWidget->GetWidgetFromName(TEXT("ScoreLeft")));
		UTextBlock* CpuTextBlock = Cast<UTextBlock>(MyScoreWidget->GetWidgetFromName(TEXT("ScoreRight")));

		if (PlayerTextBlock)
		{
			PlayerTextBlock->SetText(FText::AsNumber(PlayerScore));
		}

		if (CpuTextBlock)
		{
			CpuTextBlock->SetText(FText::AsNumber(CpuScore));
		}
	}
}
