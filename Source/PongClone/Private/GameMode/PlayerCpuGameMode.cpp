#include "GameMode/PlayerCpuGameMode.h"
#include "Paddle/PlayerPaddle.h"
#include "Paddle/CpuPaddle.h"
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
	if (PlayerPaddleClass != nullptr || CpuPaddleClass != nullptr)
	{
		SpawnPaddles();
	}
}

void APlayerCpuGameMode::SpawnPaddle(TSubclassOf<AActor> PaddleClass, const FName& SpawnTag, int32 PlayerControllerIndex = -1)
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
			if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), PlayerControllerIndex)))
			{
				PlayerController->Possess(Cast<APawn>(SpawnedPaddle));
			}
		}
	}
}

void APlayerCpuGameMode::SpawnPaddles()
{
	SpawnPaddle(PlayerPaddleClass, FName("LeftPaddleSpawn"), 0); 
	SpawnPaddle(CpuPaddleClass, FName("RightPaddleSpawn")); 
}

