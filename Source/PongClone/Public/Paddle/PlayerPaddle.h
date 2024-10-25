#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPaddle.generated.h"

struct FInputActionValue;
class UInputAction;
class UBoxComponent;
class UPaperSpriteComponent;
class UFloatingPawnMovement;
class UInputMappingContext;

UCLASS()
class PONGCLONE_API APlayerPaddle : public APawn
{
	GENERATED_BODY()

public:
	APlayerPaddle();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void MovePaddle(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* PlayerPaddleMapping;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* MovePaddleAction;

private:
	UPROPERTY(EditAnywhere, Category = "BoxComponent")
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, Category = "PaperSprite")
	UPaperSpriteComponent* PaperSprite;
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UFloatingPawnMovement* FloatingMovementComponent;
};
