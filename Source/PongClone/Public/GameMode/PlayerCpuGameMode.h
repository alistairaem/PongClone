#pragma once

#include <xstring>

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
	UPROPERTY()
	FString Player1Tag = "Player1";
	UPROPERTY()
	FString CpuTag = "CPU";
	void SpawnPaddle(const TSubclassOf<AActor>& PaddleClass, const FName& SpawnTag, int32 PlayerControllerIndex) const;

	void SpawnGoal(const FString& SpawnTag, const FString& PlayerTag) const;
public:
	APlayerCpuGameMode();

	virtual void BeginPlay() override;

	void HandleGoalScored(const FString& GoalTag);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Paddle")
	TSubclassOf<class APlayerPaddle> PlayerPaddleClass;

	UPROPERTY(EditDefaultsOnly, Category="Paddle Cpu")
	TSubclassOf<class ACpuPaddle> CpuPaddleClass;

	UPROPERTY(EditDefaultsOnly, Category="Ball")
	TSubclassOf<class ABall> BallClass;

	UPROPERTY(EditDefaultsOnly, Category="Goal")
	TSubclassOf<class AGoal> GoalClass;

	void SpawnPaddles() const;
	void SpawnBall();
	void ResetGame() const;
};
