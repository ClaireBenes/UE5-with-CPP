#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Gameplay/GoalEnum.h"
#include "AI/AIEnums.h"
#include "EnemyController.generated.h"

USTRUCT(BlueprintType)
struct FDummyStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDummyType DummyType = EDummyType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpeedDummy = 0.f;
};

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

// Speed Data Asset
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Controller|Speed")
	TObjectPtr<class UAISpeedDataAsset> AISpeedDataAsset = nullptr;

public:
	float GetAISpeedByType(EAISpeedType InType) const;
// End of Speed Data Asset
	
// Enum Example
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Controller|TEST")
	TArray <FDummyStruct> DummyArray;
	TStaticArray <FDummyStruct, (uint8)EDummyType::MAX> DummyStaticArray;
// End of Enum Example
};
