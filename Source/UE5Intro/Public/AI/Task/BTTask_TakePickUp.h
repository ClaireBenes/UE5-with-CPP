#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TakePickUp.generated.h"


UCLASS()
class UE5INTRO_API UBTTask_TakePickUp : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

protected:
	EBTNodeResult::Type Failed();

public:
	UBTTask_TakePickUp(const FObjectInitializer& ObjectInitializer);

protected:
	TObjectPtr<class AEnemyCharacter> EnemyCharacter;
	TObjectPtr<class AEnemyController> EnemyController;
	TObjectPtr<AActor> PickUp;
	TObjectPtr<class UGravityGunComponent> GravityGunComp;	

	float CurrentRandomAngleYaw = 0.0f;
	float CurrentRandomAnglePitch = 0.0f;

	UPROPERTY(EditAnywhere, Category = "PickUp")
	float RandomAngleAroundRaycast = 10.0f;
	UPROPERTY(EditAnywhere, Category = "PickUp")
	float PickUpTimer = 2.0f;
	UPROPERTY(EditAnywhere, Category = "PickUp")
	struct FBlackboardKeySelector PickUpKey;
	UPROPERTY(EditAnywhere, Category = "PickUp")
	struct FBlackboardKeySelector EnemyHasPickUpKey;
};
