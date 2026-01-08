// AI
#include "AI/EnemyController.h"
#include "AI/EnemyCharacter.h"
#include "AI/AISpeedDataAsset.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// Gameplay
#include "Gameplay/GravityGun/GravityGunComponent.h"
#include "Gameplay/MainCharacter.h"
#include "Gameplay/Goal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

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

	// Get Enemy Character
	if( AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetCharacter()) )
	{
		// Get Goals
		AGoal* PlayerGoal = EnemyCharacter->GetPlayerGoal();
		AGoal* EnemyGoal = EnemyCharacter->GetEnemyGoal();

		// Check Pointers
		if( PlayerGoal && EnemyGoal && Blackboard )
		{
			// Get Team
			Team = EnemyGoal->GetTeamType();

			// Bind on Goal Events
			PlayerGoal->OnAISphereOverlap.AddUniqueDynamic(this, &AEnemyController::OnActorOverlapAISphere);
			EnemyGoal->OnAISphereOverlap.AddUniqueDynamic(this, &AEnemyController::OnActorOverlapAISphere);

			// Set BB references
			Blackboard->SetValueAsObject(EnemyGoalBBName, EnemyGoal);
			Blackboard->SetValueAsObject(PlayerGoalBBName, PlayerGoal);

			// Check if the enemy is already inside the sphere
			if( USphereComponent* GoalSphereComponent = EnemyGoal->GetAIBehaviorCollisionSphere() )
			{
				TArray<AActor*> OverlappingActors;
				GoalSphereComponent->GetOverlappingActors(OverlappingActors, AEnemyCharacter::StaticClass());
				if( !OverlappingActors.IsEmpty() )
				{
					// Update the BB Value
					Blackboard->SetValueAsBool(EnemyIsInDefenseSphereBBName, true);
				}
			}
		}
	}

	// Example for Static Array with enum
	for( const FDummyStruct& Dummy : DummyArray )
	{
		DummyStaticArray[(uint8)Dummy.DummyType] = Dummy;
	}

	// Example of how to use DummyStaticArray
	for( const FDummyStruct& Dummy : DummyStaticArray )
	{
		FString EnumName;
		UEnum::GetValueAsString<EDummyType>(Dummy.DummyType, EnumName);
		//UE_LOG(LogTemp, Log, TEXT("%s : %f"), *EnumName, Dummy.SpeedDummy);
	}
	// Example of how to use one event
	EDummyType TypeExample7 = DummyStaticArray[(uint8) EDummyType::Example7].DummyType;
	if( TypeExample7 != EDummyType::NONE )
	{
		FString EnumName;
		UEnum::GetValueAsString<EDummyType>(DummyStaticArray[(uint8) EDummyType::Example7].DummyType, EnumName);
		//UE_LOG(LogTemp, Display, TEXT("%s : %f"), *EnumName, DummyStaticArray[(uint8) EDummyType::Example7].SpeedDummy);
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

	// Get Enemy Character
	if( AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetCharacter()) )
	{
		// Get Goals
		AGoal* PlayerGoal = EnemyCharacter->GetPlayerGoal();
		AGoal* EnemyGoal = EnemyCharacter->GetEnemyGoal();

		// Check Pointers
		if( PlayerGoal && EnemyGoal )
		{
			// Bind on Goal Events
			PlayerGoal->OnAISphereOverlap.RemoveDynamic(this, &AEnemyController::OnActorOverlapAISphere);
			EnemyGoal->OnAISphereOverlap.RemoveDynamic(this, &AEnemyController::OnActorOverlapAISphere);
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

void AEnemyController::OnActorOverlapAISphere(bool bIsOverlap, ETeamType InTeam, AActor* ActorOverlaped)
{
	// Check if it's the Enemy
	if( !ActorOverlaped->IsA(AEnemyCharacter::StaticClass()) || !Blackboard )
	{
		return;
	}

	// Update the BB Value
	Blackboard->SetValueAsBool(InTeam == Team ? EnemyIsInDefenseSphereBBName : EnemyIsInAttackSphereBBName, bIsOverlap);
}

float AEnemyController::GetMaxDistanceFromGoal() const
{
	return MaxDistanceFromGoal;
}

float AEnemyController::GetAISpeedByType(EAISpeedType InType) const
{
	// Check for Data Asset
	if( AISpeedDataAsset )
	{
		return AISpeedDataAsset->SpeedByTypeMap[(uint8) InType];
	}
	return 0.0f;
}

void AEnemyController::OnPickUpTimerEnd()
{
	// Update BB Value
	if( Blackboard )
	{
		Blackboard->SetValueAsBool(CanTakePickUpBBName, true);
	}

	// Clear Timer
	GetCharacter()->GetWorldTimerManager().ClearTimer(PickUpTimer);
}

void AEnemyController::StartPickUpTimer(float InTime)
{
	// Check BB
	if( !Blackboard )
	{
		return;
	}

	// Update BB Value
	Blackboard->SetValueAsBool(CanTakePickUpBBName, false);

	// Prepare Timer
	GetCharacter()->GetWorldTimerManager().ClearTimer(PickUpTimer);
	GetCharacter()->GetWorldTimerManager().SetTimer(PickUpTimer, this, &AEnemyController::OnPickUpTimerEnd, InTime, false);
}
