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

protected:
	UPROPERTY(EditDefaultsOnly, Category="Paddle")
	TSubclassOf<class APlayerPaddle> PlayerPaddleClass;

	void SpawnPaddles();
};


