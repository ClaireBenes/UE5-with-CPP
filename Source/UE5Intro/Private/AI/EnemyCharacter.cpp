#include "AI/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


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

void AEnemyCharacter::SetMaxWalkSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

