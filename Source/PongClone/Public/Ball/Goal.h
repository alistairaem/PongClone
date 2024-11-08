#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

class UPaperFlipbookComponent;
class APlayerCpuGameMode;
class UBoxComponent;
class UAudioComponent;

UCLASS()
class PONGCLONE_API AGoal : public AActor
{
	GENERATED_BODY()

public:
	AGoal();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBoxIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category = "BoxComponent")
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, Category = "PaperFlipbook")
	UPaperFlipbookComponent* PaperFlipbook;
	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* GoalHitSound;
	UPROPERTY()
	UAudioComponent* AudioComponent;
	UPROPERTY()
	APlayerCpuGameMode* GameMode;

	void GoalScored() const;
};
