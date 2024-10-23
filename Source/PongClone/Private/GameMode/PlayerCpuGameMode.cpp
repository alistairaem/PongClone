// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlayerCpuGameMode.h"
#include "Paddle/PlayerPaddle.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

APlayerCpuGameMode::APlayerCpuGameMode()
{
	DefaultPawnClass = nullptr;
	static ConstructorHelpers::FClassFinder<APlayerPaddle> PaddleBPClass(TEXT("/Game/BluePrints/BP_PlayerPaddle"));
	if (PaddleBPClass.Class != nullptr)
	{
		PlayerPaddleClass = PaddleBPClass.Class;
	}
}

void APlayerCpuGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnPaddles();
}

void APlayerCpuGameMode::SpawnPaddles()
{
	TArray<AActor*> LeftSpawnPoints;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("LeftPaddleSpawn"), LeftSpawnPoints);

	if (LeftSpawnPoints.Num() > 0 && PlayerPaddleClass)
	{
		AActor* LeftSpawnPoint = LeftSpawnPoints[0];
		FVector SpawnLocation = LeftSpawnPoint->GetActorLocation();
		FRotator SpawnRotation = LeftSpawnPoint->GetActorRotation();
		APlayerPaddle* SpawnedPaddle = GetWorld()->SpawnActor<APlayerPaddle>(
			PlayerPaddleClass, SpawnLocation, SpawnRotation);
		if (SpawnedPaddle)
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(
				UGameplayStatics::GetPlayerController(GetWorld(), 0)))
			{
				PlayerController->Possess(SpawnedPaddle);
			}
		}
	}
}
