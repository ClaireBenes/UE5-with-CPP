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
	void OnScoreUpdated(unsigned int CurrentScore, FString GoalName);

protected:
	TArray<AActor*> Goals;
	TMap<FString, uint32> GoalScores;
};
