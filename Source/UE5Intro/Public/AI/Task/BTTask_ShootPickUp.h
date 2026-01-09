#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ShootPickUp.generated.h"


UCLASS()
class UE5INTRO_API UBTTask_ShootPickUp : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual FString GetStaticDescription() const override;
	
protected:
	TObjectPtr<class AEnemyCharacter> EnemyCharacter;
	TObjectPtr<class AEnemyController> EnemyController;

	TObjectPtr<AActor> PlayerGoal;
	TObjectPtr<class UGravityGunComponent> GravityGunComp;

	UPROPERTY(EditAnywhere, Category = "Pick Up")
	float PickUpTimer = 2.f;
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	struct FBlackboardKeySelector PlayerGoalKey;
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	struct FBlackboardKeySelector EnemyHasPickUpKey;
};
