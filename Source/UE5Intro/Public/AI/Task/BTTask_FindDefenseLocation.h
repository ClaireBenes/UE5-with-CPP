#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindDefenseLocation.generated.h"


UCLASS()
class UE5INTRO_API UBTTask_FindDefenseLocation : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

protected:
	bool FindDefenseLocation(AActor* Goal, float DefenseDist, FVector& OutDefenseLocation);

public:
	UBTTask_FindDefenseLocation(const FObjectInitializer& ObjectInitializer);

protected:
	TObjectPtr<class AEnemyCharacter> EnemyCharacter;
	TObjectPtr<class AEnemyController> EnemyController;

	// Display Variables
	TWeakObjectPtr<AActor> EnemyGoal;
	FVector DefenseLocation;
	float DefenseDistanceFromGoal;

	UPROPERTY(EditAnywhere, Category = "Defense")
	struct FBlackboardKeySelector EnemyGoalKey;
	UPROPERTY(EditAnywhere, Category = "Defense")
	struct FBlackboardKeySelector DefenseLocationKey;
	
};
