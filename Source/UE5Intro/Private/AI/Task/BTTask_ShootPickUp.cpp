//AI
#include "AI/Task/BTTask_ShootPickUp.h"
#include "AI/EnemyCharacter.h"
#include "AI/EnemyController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/BlackboardComponent.h"

// Gameplay
#include "Gameplay/GravityGun/GravityGunComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_ShootPickUp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	// Get Gravity Gun Component
	GravityGunComp = EnemyCharacter->FindComponentByClass<UGravityGunComponent>();
	if( !GravityGunComp )
	{
		return EBTNodeResult::Failed;
	}

	// Get Values from Blackboard
	PlayerGoal = Cast<AActor>(BlackboardComp->GetValueAsObject(PlayerGoalKey.SelectedKeyName));
	if( !PlayerGoal )
	{
		return EBTNodeResult::Failed;
	}

	// Check for obstacles
	const FVector RaycastStart = EnemyCharacter->GetActorLocation();
	const FVector RaycastEnd = PlayerGoal->GetActorLocation();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(EnemyCharacter.Get());
	Params.AddIgnoredActor(PlayerGoal);
	FHitResult HitResult;

	// Launch Raycast
	if( GetWorld()->LineTraceSingleByChannel(HitResult, RaycastStart, RaycastEnd, ECC_Visibility, Params) )
	{
		return EBTNodeResult::Failed;
	}

	// Launch Pick Up and Timer
	GravityGunComp->ReleasePickUp(true);
	EnemyController->StartPickUpTimer(PickUpTimer);

	// Update BB Values
	BlackboardComp->SetValueAsBool(EnemyHasPickUpKey.SelectedKeyName, false);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_ShootPickUp::GetStaticDescription() const
{
	FString StaticDescription("invalid");
	if( ( PlayerGoalKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass() )
		|| ( EnemyHasPickUpKey.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass() ) )
	{
		StaticDescription = FString::Printf(TEXT("Player Goal: %s - Enemy Has Pick Up: %s"),
			*PlayerGoalKey.SelectedKeyName.ToString(), *EnemyHasPickUpKey.SelectedKeyName.ToString());
	}

	return FString::Printf(TEXT("%s : %s"), *Super::GetStaticDescription(), *StaticDescription);
}
