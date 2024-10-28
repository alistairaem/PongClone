#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerCpuGameMode.generated.h"

class ABall;
/**
 * 
 */
UCLASS()
class PONGCLONE_API APlayerCpuGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	int PlayerScore = 0;
	int CpuScore = 0;
	UPROPERTY()
	ABall* SpawnedBall;
	UPROPERTY()
	AActor* BallSpawnPoint;

public:
	APlayerCpuGameMode();

	virtual void BeginPlay() override;
	void SpawnPaddle(TSubclassOf<AActor> PaddleClass, const FName& SpawnTag, int32 PlayerControllerIndex);

	void HandleGoalScored();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Paddle")
	TSubclassOf<class APlayerPaddle> PlayerPaddleClass;

	UPROPERTY(EditDefaultsOnly, Category="Paddle Cpu")
	TSubclassOf<class ACpuPaddle> CpuPaddleClass;

	UPROPERTY(EditDefaultsOnly, Category="Ball")
	TSubclassOf<class ABall> BallClass;

	void SpawnPaddles();
	void SpawnBall();
	void ResetGame();
};
