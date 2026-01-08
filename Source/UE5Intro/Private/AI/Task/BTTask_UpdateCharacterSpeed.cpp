#include "AI/Task/BTTask_UpdateCharacterSpeed.h"
#include "AI/EnemyCharacter.h"
#include "AI/EnemyController.h"

EBTNodeResult::Type UBTTask_UpdateCharacterSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	// Get Speed
	CharacterSpeed = EnemyController->GetAISpeedByType(SpeedType);

	// Apply Speed
	EnemyCharacter->SetMaxWalkSpeed(CharacterSpeed);

	return EBTNodeResult::Succeeded;
}

void UBTTask_UpdateCharacterSpeed::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	// At runtime, we want to display the speed
	Values.Add(FString::Printf(TEXT("Character Speed: %f"), CharacterSpeed));
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
}

FString UBTTask_UpdateCharacterSpeed::GetStaticDescription() const
{
	// Display Enum Selected
	FString EnumName;
	UEnum::GetValueAsString<EAISpeedType>(SpeedType, EnumName);
	return FString::Printf(TEXT("%s : %s"), *Super::GetStaticDescription(), *EnumName);
}
