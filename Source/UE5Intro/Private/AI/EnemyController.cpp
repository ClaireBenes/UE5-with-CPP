// AI
#include "AI/EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Start the enemy behaviour tree
	if( EnemyBehaviorTree )
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
}
