#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerCpuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONGCLONE_API APlayerCpuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlayerCpuGameMode();

	virtual void BeginPlay() override;
	void SpawnPaddle(TSubclassOf<AActor> PaddleClass, const FName& SpawnTag, int32 PlayerControllerIndex);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Paddle")
	TSubclassOf<class APlayerPaddle> PlayerPaddleClass;

	UPROPERTY(EditDefaultsOnly, Category="Paddle Cpu")
	TSubclassOf<class ACpuPaddle> CpuPaddleClass;

	void SpawnPaddles();
};


