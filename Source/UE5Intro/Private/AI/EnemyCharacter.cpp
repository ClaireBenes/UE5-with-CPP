#include "AI/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

AGoal* AEnemyCharacter::GetPlayerGoal() const
{
	return PlayerGoal;
}

AGoal* AEnemyCharacter::GetEnemyGoal() const
{
	return EnemyGoal;
}

