#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"


UCLASS(Abstract)
class UE5INTRO_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

// Behaviour Tree and Blackboard values
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Controller|Behavior Tree")
	TObjectPtr<class UBehaviorTree> EnemyBehaviorTree = nullptr;

// End of Behaviour Tree and Blackboard values
	
};
