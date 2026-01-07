#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS(Abstract)
class UE5INTRO_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

// Goal
protected:
	UPROPERTY(EditInstanceOnly, Category = "Enemy Character")
	TObjectPtr<class AGoal> PlayerGoal = nullptr;
	UPROPERTY(EditInstanceOnly, Category = "Enemy Character")
	TObjectPtr<class AGoal> EnemyGoal = nullptr;

public:
	class AGoal* GetPlayerGoal() const;
	class AGoal* GetEnemyGoal() const;
// End of Goal

};
