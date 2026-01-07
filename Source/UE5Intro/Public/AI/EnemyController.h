#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Gameplay/GoalEnum.h"
#include "EnemyController.generated.h"


UCLASS(Abstract)
class UE5INTRO_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnPossess(APawn* InPawn) override;

// Behaviour Tree and Blackboard values
protected:
	UFUNCTION()
	void OnPlayerHasPickUp(bool bInPlayerHasPickUp);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Controller|Behavior Tree")
	TObjectPtr<class UBehaviorTree> EnemyBehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy Controller|Behavior Tree|Blackboard Names")
	FName PlayerHasPickUpBBName = "PlayerHasPickUp";
	
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Controller|Behavior Tree|Blackboard Names")
	FName EnemyIsInDefenseSphereBBName = "EnemyIsInDefenseSphere";
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Controller|Behavior Tree|Blackboard Names")
	FName EnemyIsInAttackSphereBBName = "EnemyIsInAttackSphere";

	UPROPERTY(EditDefaultsOnly, Category = "Enemy Controller|Behavior Tree|Blackboard Names")
	FName PlayerGoalBBName = "PlayerGoal";
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Controller|Behavior Tree|Blackboard Names")
	FName EnemyGoalBBName = "EnemyGoal";
// End of Behaviour Tree and Blackboard values

// Goal
protected:
	UFUNCTION()
	void OnActorOverlapAISphere(bool bIsOverlap, ETeamType InTeam, AActor* ActorOverlaped);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Enemy Controller")
	ETeamType Team = ETeamType::None;
// End of Goal
	
};
