#include "Paddle/PlayerPaddle.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"


APlayerPaddle::APlayerPaddle()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(9.0f, 1.0f, 60.0f));
	RootComponent = BoxComponent;

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	PaperSprite->SetupAttachment(RootComponent);

	FloatingMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingMovementComponent->MaxSpeed = 1000.0f;
}

void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
}


void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerPaddleMapping, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			if (MovePaddleAction)
			{
				EnhancedInputComponent->BindAction(MovePaddleAction, ETriggerEvent::Triggered, this,
				                                   &APlayerPaddle::MovePaddle);
			}
		}
	}
}

void APlayerPaddle::MovePaddle(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	if (AxisValue != 0.0f)
	{
		AddMovementInput(FVector(0.0f, AxisValue, 0.0f), 0.4f);
	}
}
