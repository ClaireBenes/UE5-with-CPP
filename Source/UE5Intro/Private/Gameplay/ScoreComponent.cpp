#include "Gameplay/ScoreComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Gameplay/Goal.h"

UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UScoreComponent::ShowGoalsScore()
{
	if( GoalScores.Num() == 0 )
	{
		UE_LOG(LogTemp, Log, TEXT("No goals have been scored yet."));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("=== Current Goal Scores ==="));
	for( const TPair<FString, uint32>& Entry : GoalScores )
	{
		UE_LOG(LogTemp, Log, TEXT("'%s': %d points"), *Entry.Key, Entry.Value);
	}
}

void UScoreComponent::BeginPlay()
{	
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGoal::StaticClass(), Goals);
	for( int i = 0; i < Goals.Num(); i++ )
	{
		if( Goals[i] )
		{
			Cast<AGoal>(Goals[i])->OnGoalScored.AddUniqueDynamic(this, &UScoreComponent::OnScoreUpdated);

			const FString GoalName = UKismetSystemLibrary::GetDisplayName(Goals[i]);
			GoalScores.FindOrAdd(GoalName) = 0;
		}
	}
}

void UScoreComponent::OnScoreUpdated(unsigned int CurrentScore, FString GoalName)
{
	GoalScores.FindOrAdd(GoalName) = CurrentScore;
}

