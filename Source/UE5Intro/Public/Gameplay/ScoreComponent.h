#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"


UCLASS(ClassGroup = ( "Score" ), meta = ( BlueprintSpawnableComponent ))
class UE5INTRO_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UScoreComponent();	

	void ShowGoalsScore();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnScoreUpdated(ETeamType TeamType);

protected:
	TArray<class AGoal*> Goals;
	TMap<ETeamType, uint32> GoalScores;

// Pick Up In Goal
public:
	void CountPickUpInGoal();

// end of Pick Up In Goal
};
