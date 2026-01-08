#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "Gameplay/GoalEnum.h"
#include "EnvQueryTest_AITeam.generated.h"


UCLASS(MinimalAPI)
class UEnvQueryTest_AITeam : public UEnvQueryTest
{
	GENERATED_UCLASS_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Team")
	ETeamType Team = ETeamType::None;

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
};
