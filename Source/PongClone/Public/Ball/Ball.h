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
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere, Category = "PaperSprite")
	UPaperSpriteComponent* PaperSprite;
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed = 600.0f;

	FVector Direction;

	void MoveBall(float DeltaTime);
	void Bounce(const FVector& Normal);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse,
	           const FHitResult& Hit);
};
