#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Gameplay/GoalEnum.h"
#include "AITargetPoint.generated.h"


UCLASS()
class UE5INTRO_API AAITargetPoint : public ATargetPoint
{
	GENERATED_BODY()


public:
	ETeamType GetTeam() const;

protected:
	UPROPERTY(EditInstanceOnly, Category = "Ai Target Point")
	ETeamType TeamType = ETeamType::None;
	
};
