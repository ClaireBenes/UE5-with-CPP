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

ETeamType AGoal::GetTeamType()
{
	return TeamType;
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
	OnGoalScored.Broadcast(TeamType);
	
}

unsigned int AGoal::CountPickUpInGoal()
{
	if( !CollisionBox )
	{
		return 0;
	}

	// We can use Overlapping Actors but we will need to cast them after
	if( bUseOverlappingActorsFunction )
	{
		// Get Actors
		TArray<AActor*> OverlappingActors;
		CollisionBox->GetOverlappingActors(OverlappingActors);

		// Check if they are Pick Ups
		unsigned int PickUpInGoal = 0;
		for( AActor* OverlappingActor : OverlappingActors )
		{
			if( OverlappingActor->FindComponentByClass<UPickUpComponent>() )
			{
				PickUpInGoal++;
			}
		}
		return PickUpInGoal;
	}
	else
	{
		// Prepare Box Cast location
		const FVector GoalLocation = GetActorLocation();
		const FRotator GoalRotation = GetActorRotation();
		const FVector ScaledBoxExtent = CollisionBox->GetScaledBoxExtent();

		// Prepare Box Cast Array
		TArray<FHitResult> HitResults;
		TArray<AActor*> ActorsToIgnore;

		UKismetSystemLibrary::BoxTraceMulti(GetWorld(), GoalLocation, GoalLocation, ScaledBoxExtent, GoalRotation,
			GoalTraceChannel, false, ActorsToIgnore, EDrawDebugTrace::None, HitResults, true);

		// Return result
		const unsigned int PickUpInGoal = HitResults.Num();
		return PickUpInGoal;
	}	
}
