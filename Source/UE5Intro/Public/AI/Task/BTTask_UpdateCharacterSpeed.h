#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI/AIEnums.h"
#include "BTTask_UpdateCharacterSpeed.generated.h"


UCLASS()
class UE5INTRO_API UBTTask_UpdateCharacterSpeed : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;
	
protected:
	TObjectPtr<class AEnemyCharacter> EnemyCharacter;
	TObjectPtr<class AEnemyController> EnemyController;

	// For Description
	float CharacterSpeed = 0.0f;

	UPROPERTY(Category = "Speed", EditAnywhere)
	EAISpeedType SpeedType = EAISpeedType::Normal;
};
