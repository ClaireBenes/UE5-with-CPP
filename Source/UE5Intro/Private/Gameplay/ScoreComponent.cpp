#include "Gameplay/ScoreComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Gameplay/Goal.h"

UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UScoreComponent::BeginPlay()
{	
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGoal::StaticClass(), Actors);

	for( int i = 0; i < Actors.Num(); i++ )
	{
		AGoal* GoalCasted = Cast<AGoal>(Actors[i]);
		if( GoalCasted )
		{
			Goals.Add(GoalCasted);
			GoalCasted->OnGoalScored.AddUniqueDynamic(this, &UScoreComponent::OnScoreUpdated);

			GoalScores.FindOrAdd(GoalCasted->GetTeamType()) = 0;
		}
	}
}

void UScoreComponent::OnScoreUpdated(ETeamType TeamType)
{
	unsigned int& TeamScore = GoalScores.FindOrAdd(TeamType);
	TeamScore++;
}

void UScoreComponent::CountPickUpInGoal()
{
	if( !Goals.Num() )
	{
		UE_LOG(LogTemp, Log, TEXT("There is no goals on the map !"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("=== Current Pick Up in Goals ==="));
	for( AGoal* Goal : Goals )
	{
		if( Goal )
		{
			unsigned int PickUpInGoal = Goal->CountPickUpInGoal();
			const FString GoalName = UKismetSystemLibrary::GetDisplayName(Goal);
			UE_LOG(LogTemp, Log, TEXT("There is %d pick up inside the goal %s"), PickUpInGoal, *GoalName);
		}
	}
}

void UScoreComponent::ShowGoalsScore()
{
	if( GoalScores.Num() == 0 )
	{
		UE_LOG(LogTemp, Log, TEXT("No goals have been scored yet."));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("=== Current Goal Scores ==="));
	for( const TPair<ETeamType, uint32>& Entry : GoalScores )
	{
		FString TeamName = StaticEnum<ETeamType>()->GetValueAsString(Entry.Key);
		UE_LOG(LogTemp, Log, TEXT("%s: %d points"), *TeamName, Entry.Value);
	}
}

