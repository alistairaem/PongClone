#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class USphereComponent;
class UPaperSpriteComponent;

UCLASS()
class PONGCLONE_API ABall : public AActor
{
	GENERATED_BODY()

public:
	ABall();

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse, const FHitResult& Hit);
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void ResetBall();
	void SetRandomDirection();
	FVector GetDirection() const { return Direction; }

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere, Category = "PaperSprite")
	UPaperSpriteComponent* PaperSprite;
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed = 300.0f;
	FTimerHandle DirectionResetTimerHandle;

	FVector Direction;

	void MoveBall(float DeltaTime);
	void Bounce(const FVector& Normal);
};
