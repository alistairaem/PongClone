#include "Ball/Goal.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Ball/Ball.h"
#include "Components/AudioComponent.h"
#include "GameMode/PlayerCpuGameMode.h"
#include "Engine/World.h"

AGoal::AGoal()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbook"));
	PaperFlipbook->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AGoal::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<APlayerCpuGameMode>(GetWorld()->GetAuthGameMode());
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoal::BeginOverlap);
	AudioComponent->SetSound(GoalHitSound);
}

void AGoal::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                         int32 OtherBoxIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABall::StaticClass()))
	{
		GoalScored();
	}
}

void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoal::GoalScored() const
{
	if (GameMode == nullptr) return;
	GameMode->HandleGoalScored(BoxComponent->ComponentTags[0].ToString());
	if (AudioComponent == nullptr) return;
	const float RandomPitch = FMath::FRandRange(0.75f, 1.25f);
	AudioComponent->SetPitchMultiplier(RandomPitch);
	AudioComponent->Play();
}
