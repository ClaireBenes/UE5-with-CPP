#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "Gameplay/GoalEnum.h"
#include "EnvQueryContext_Goal.generated.h"


UCLASS(Blueprintable, Abstract, MinimalAPI)
class UEnvQueryContext_Goal : public UEnvQueryContext
{
	GENERATED_BODY()

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

	UPROPERTY(EditAnywhere, Category = "Goal")
	TSubclassOf<AActor> GoalBP = nullptr;
	UPROPERTY(EditAnywhere, Category = "Goal")
	ETeamType Team = ETeamType::None;
};
