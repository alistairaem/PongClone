#include "Ball/Ball.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	PaperSprite->SetupAttachment(RootComponent);
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                  FVector NormalImpulse, const FHitResult& Hit)
{
	Bounce(Hit.Normal);
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentHit.AddDynamic(this, &ABall::OnHit);
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveBall(DeltaTime);
}

void ABall::ResetBall()
{
	Direction = FVector(0.0f, 0.0f, 0.0f);
	GetWorld()->GetTimerManager().SetTimer(DirectionResetTimerHandle, this, &ABall::SetRandomDirection, 1.0f, false);
}

void ABall::SetRandomDirection()
{
	float RandomX = FMath::FRandRange(-1.0f, 1.0f);
	float RandomY = FMath::FRandRange(-1.0f, 1.0f);
	Direction = FVector(RandomX, RandomY, 0.0f).GetSafeNormal();
}

void ABall::MoveBall(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + (Direction * Speed * DeltaTime);
	SetActorLocation(NewLocation, true);
}

void ABall::Bounce(const FVector& Normal)
{
	Direction = Direction.MirrorByVector(Normal);
}
