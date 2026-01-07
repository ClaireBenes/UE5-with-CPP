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
// End of Behaviour Tree and Blackboard values
	
};
