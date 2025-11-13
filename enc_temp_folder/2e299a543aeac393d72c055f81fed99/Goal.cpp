#include "Gameplay/Goal.h"

// Gameplay
#include "Components/BoxComponent.h"

AGoal::AGoal(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the collision box
	CollisionBox = ObjectInitializer.CreateOptionalDefaultSubobject<UBoxComponent>(this, TEXT("CollisionBox"));
	if( CollisionBox )
	{
		SetRootComponent(CollisionBox);
	}
}

void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

