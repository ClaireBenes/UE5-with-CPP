// AI
#include "AI/Test/EnvQueryContext_Goal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Gameplay/Goal.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"


// System
#include "Kismet/GameplayStatics.h"


void UEnvQueryContext_Goal::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	// Check our Querierr
	UObject* QueryObject = QueryInstance.Owner.Get();
	if( !QueryObject )
	{
		return;
	}

	// Check that our Goal BP is set
	if( !GoalBP )
	{
		return;
	}

	// Get all Goal of Map
	TArray<AActor*> GoalArray, GoalTeamArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), GoalBP, GoalArray);
	if( GoalArray.IsEmpty() )
	{
		return;
	}

	// For each goal, check the Team
	for( AActor* Goal : GoalArray )
	{
		// Cast the Actor
		if( AGoal* CastGoal = Cast<AGoal>(Goal) )
		{
			if( CastGoal->GetTeamType() == Team )
			{
				GoalTeamArray.Add(Goal);
			}
		}
	}

	// Send Context result 
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, GoalTeamArray);
}
