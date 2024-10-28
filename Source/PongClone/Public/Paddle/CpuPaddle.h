#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CpuPaddle.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;
class UFloatingPawnMovement;

UCLASS()
class PONGCLONE_API ACpuPaddle : public AActor
{
	GENERATED_BODY()

public:
	ACpuPaddle();

protected:
	virtual void BeginPlay() override;
	void MovePaddle(float Value, float DeltaTime);
	void CheckBallPosition(float DeltaTime);

	UPROPERTY()
	AActor* Ball;

	UPROPERTY(EditAnywhere, Category = "Paddle Speed")
	float PaddleSpeed = 100.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "BoxComponent")
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, Category = "OverlapComponent")
	UBoxComponent* OverlapComponent;
	UPROPERTY(EditAnywhere, Category = "PaperSprite")
	UPaperSpriteComponent* PaperSprite;

	bool IsTopCollision = false;
	bool IsBottomCollision = false;
};
