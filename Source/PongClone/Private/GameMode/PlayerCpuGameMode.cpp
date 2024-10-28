#include "GameMode/PlayerCpuGameMode.h"
#include "Paddle/PlayerPaddle.h"
#include "Paddle/CpuPaddle.h"
#include "Ball/Ball.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

APlayerCpuGameMode::APlayerCpuGameMode()
{
	DefaultPawnClass = nullptr;
}

void APlayerCpuGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (BallClass != nullptr)
	{
		SpawnBall();
	}
	if (PlayerPaddleClass != nullptr || CpuPaddleClass != nullptr)
	{
		SpawnPaddles();
	}
}

void APlayerCpuGameMode::SpawnPaddle(TSubclassOf<AActor> PaddleClass, const FName& SpawnTag,
                                     int32 PlayerControllerIndex = -1)
{
	TArray<AActor*> SpawnPoints;
	UGameplayStatics::GetAllActorsWithTag(this, SpawnTag, SpawnPoints);

	if (SpawnPoints.Num() > 0 && PaddleClass)
	{
		AActor* SpawnPoint = SpawnPoints[0];
		FVector SpawnLocation = SpawnPoint->GetActorLocation();
		FRotator SpawnRotation = SpawnPoint->GetActorRotation();

		AActor* SpawnedPaddle = GetWorld()->SpawnActor<AActor>(PaddleClass, SpawnLocation, SpawnRotation);

		if (PlayerControllerIndex >= 0 && SpawnedPaddle)
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(
				UGameplayStatics::GetPlayerController(GetWorld(), PlayerControllerIndex)))
			{
				PlayerController->Possess(Cast<APawn>(SpawnedPaddle));
			}
		}
	}
}

void APlayerCpuGameMode::HandleGoalScored()
{
	ResetGame();
}

void APlayerCpuGameMode::SpawnPaddles()
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
		FRotator SpawnRotation = BallSpawnPoint->GetActorRotation();

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(BallActorClass, SpawnLocation, SpawnRotation);
		SpawnedBall = Cast<ABall>(SpawnedActor);
		SpawnedBall->ResetBall();
	}
}

void APlayerCpuGameMode::ResetGame()
{
	if (SpawnedBall)
	{
		SpawnedBall->GetActorLocation() = BallSpawnPoint->GetActorLocation();
		SpawnedBall->GetActorRotation() = BallSpawnPoint->GetActorRotation();
		SpawnedBall->ResetBall();
	}
}
