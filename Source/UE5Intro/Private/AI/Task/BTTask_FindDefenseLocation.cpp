//AI 
#include "AI/Task/BTTask_FindDefenseLocation.h"
#include "AI/EnemyCharacter.h"
#include "AI/EnemyController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

// System
#include "Kismet/GameplayStatics.h"


UBTTask_FindDefenseLocation::UBTTask_FindDefenseLocation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Add filter to EnemyGoalKey, Object only
	EnemyGoalKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindDefenseLocation, EnemyGoalKey), AActor::StaticClass());

	// Add filter to DefenseLocationKey, Vector only
	DefenseLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindDefenseLocation, EnemyGoalKey));
}

EBTNodeResult::Type UBTTask_FindDefenseLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Controller and Character
	if( EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner()) )
	{
		EnemyCharacter = Cast<AEnemyCharacter>(EnemyController->GetPawn());
	}

	// Return failed if no pointers
	if( !EnemyCharacter )
	{
		return EBTNodeResult::Failed;
	}

	// Get Blackboard
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if( !BlackboardComp )
	{
		return EBTNodeResult::Failed;
	}

	// Get Values from Blackboard
	EnemyGoal = Cast<AActor>(BlackboardComp->GetValueAsObject(EnemyGoalKey.SelectedKeyName));
	if( !EnemyGoal.IsValid() )
	{
		return EBTNodeResult::Failed;
	}

	// Get Max Distance from Goal
	DefenseDistanceFromGoal = EnemyController->GetMaxDistanceFromGoal();

	// Try to find the defense location
	if( !FindDefenseLocation(EnemyGoal.Get(), DefenseDistanceFromGoal, DefenseLocation) )
	{
		return EBTNodeResult::Aborted;
	}

	// Set Value in Blackboard
	BlackboardComp->SetValueAsVector(DefenseLocationKey.SelectedKeyName, DefenseLocation);
	return EBTNodeResult::Succeeded;
}

void UBTTask_FindDefenseLocation::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	// At runtime, we want to display the found Location
	Values.Add(FString::Printf(TEXT("Defense Location: %s"), *DefenseLocation.ToString()));
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
}

FString UBTTask_FindDefenseLocation::GetStaticDescription() const
{
	// We need to make sure that EnemyGoalKey is an Object, and DefenseLocationKey is a Vector
	FString StaticDescription("invalid");
	if( (EnemyGoalKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass()) 
		|| ( DefenseLocationKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass()) )
	{
		StaticDescription = FString::Printf(TEXT("Goal: %s - Defense Location: %s"), 
			*EnemyGoalKey.SelectedKeyName.ToString(), *DefenseLocationKey.SelectedKeyName.ToString());
	}

	return FString::Printf(TEXT("%s : %s"), *Super::GetStaticDescription(), *StaticDescription);
}

bool UBTTask_FindDefenseLocation::FindDefenseLocation(AActor* Goal, float DefenseDist, FVector& OutDefenseLocation)
{
	// Get Player Character
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if( !PlayerCharacter || !Goal)
	{
		return false;
	}

	// Get Location
	const FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	const FVector GoalLocation = Goal->GetActorLocation();

	// Create Vector that we'll use for defense location
	const FVector GoalToPlayer = PlayerLocation - GoalLocation;
	FVector GoalToPlayerNorm = GoalToPlayer;
	GoalToPlayerNorm.Normalize();

	// Place the enemy in the middle of this Vector
	OutDefenseLocation = GoalLocation + ( GoalToPlayerNorm * (GoalToPlayer.Size() / 2.0f) );

	// We don't want the Enemy to be above DefenseDistanceFromGoal from GoalLocation
	if( FVector::Distance(GoalLocation, OutDefenseLocation) > DefenseDistanceFromGoal )
	{
		OutDefenseLocation = GoalLocation + ( GoalToPlayerNorm * DefenseDistanceFromGoal );
	}

	return true;
}

