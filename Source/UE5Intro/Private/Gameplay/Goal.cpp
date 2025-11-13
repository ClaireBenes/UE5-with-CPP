#include "Gameplay/Goal.h"

// Gameplay
#include "Components/BoxComponent.h"
#include "Gameplay/PickUpComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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
	
	// Bind to the overlap event
	if( CollisionBox )
	{
		CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGoal::OnGoalOverlap);
	}
}

void AGoal::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Bind from the overlap event
	if( CollisionBox )
	{
		CollisionBox->OnComponentBeginOverlap.RemoveDynamic(this, &AGoal::OnGoalOverlap);
	}
}

void AGoal::OnGoalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if it's a Pick Up
	if( !OtherActor->FindComponentByClass<UPickUpComponent>() )
	{
		return;
	}

	// Update the score and display it
	Score++;
	const FString GoalName = UKismetSystemLibrary::GetDisplayName(OtherActor);
	UE_LOG(LogTemp, Log, TEXT("The score of %s is %d"), *GoalName, Score);
	
}

