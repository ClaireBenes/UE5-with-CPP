// AI
#include "AI/EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// Gameplay
#include "Gameplay/GravityGun/GravityGunComponent.h"
#include "Gameplay/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	// Get the player (not the AI)
	if( AMainCharacter* Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) )
	{
		// Get Gravity gun Component
		if( UGravityGunComponent* GravityGunComp = Player->FindComponentByClass<UGravityGunComponent>() )
		{
			GravityGunComp->OnPlayerHasPickUp.AddUniqueDynamic(this, &AEnemyController::OnPlayerHasPickUp);
		}
	}
}

void AEnemyController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Get the player (not the AI)
	if( AMainCharacter* Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)) )
	{
		// Get Gravity gun Component
		if( UGravityGunComponent* GravityGunComp = Player->FindComponentByClass<UGravityGunComponent>() )
		{
			GravityGunComp->OnPlayerHasPickUp.RemoveDynamic(this, &AEnemyController::OnPlayerHasPickUp);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Start the enemy behaviour tree
	if( EnemyBehaviorTree )
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
}

void AEnemyController::OnPlayerHasPickUp(bool bInPlayerHasPickUp)
{
	// Update Blackboard value
	if( Blackboard )
	{
		Blackboard->SetValueAsBool(PlayerHasPickUpBBName,bInPlayerHasPickUp);
	}
}
