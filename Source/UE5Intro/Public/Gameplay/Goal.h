#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGoalScoredDelegate, unsigned int, CurrentScore, FString, GoalName);

UCLASS(Abstract)
class UE5INTRO_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	AGoal(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

// Collision Box
public:
	//void FOnGoalScoredDelegate(float CurrentScore, FString GoalName);

	FOnGoalScoredDelegate OnGoalScored;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> CollisionBox = nullptr;

	unsigned int Score = 0;

protected:
	UFUNCTION()
	void OnGoalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// end of Collision Box
};
