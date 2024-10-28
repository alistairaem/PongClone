#include "Ball/Ball.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "Math/UnrealMathUtility.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	SphereComponent->OnComponentHit.AddDynamic(this, &ABall::OnHit);

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	PaperSprite->SetupAttachment(RootComponent);
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABall::MoveBall(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + (Direction * Speed * DeltaTime);
	SetActorLocation(NewLocation);
}

void ABall::Bounce(const FVector& Normal)
{
	Direction = FVector::DotProduct(Direction, Normal) * Normal;
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                  FVector NormalImpulse, const FHitResult& Hit)
{
	Bounce(Hit.Normal);
}
