// AI
#include "AI/Task/BTTask_TakePickUp.h"
#include "AI/EnemyCharacter.h"
#include "AI/EnemyController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/BlackboardComponent.h"

// Gameplay
#include "Gameplay/GravityGun/GravityGunComponent.h"
#include "Kismet/GameplayStatics.h"


UBTTask_TakePickUp::UBTTask_TakePickUp(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Add filter to PickUpKey, Object only
	PickUpKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_TakePickUp, PickUpKey), AActor::StaticClass());

	// Add filter to EnemyHasPickUpKey, Bool only
	EnemyHasPickUpKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_TakePickUp, EnemyHasPickUpKey));
}

EBTNodeResult::Type UBTTask_TakePickUp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Controller and Character
	if( EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner()) )
	{
		EnemyCharacter = Cast<AEnemyCharacter>(EnemyController->GetPawn());
	}

	// Return failed if no pointers
	if( !EnemyCharacter )
	{
		return Failed();
	}

	// Get Blackboard
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if( !BlackboardComp )
	{
		return Failed();
	}

	// Get Gravity Gun Component
	GravityGunComp = EnemyCharacter->FindComponentByClass<UGravityGunComponent>();
	if( !GravityGunComp )
	{
		return Failed();
	}

	// Get Values from Blackboard
	PickUp = Cast<AActor>(BlackboardComp->GetValueAsObject(PickUpKey.SelectedKeyName));
	if( !PickUp )
	{
		return Failed();
	}

	// Check if we're close enough
	const FVector EnemyLocation = EnemyCharacter->GetActorLocation();
	const FVector PickUpLocation = PickUp->GetActorLocation();
	FVector EnemyToPickUp = PickUpLocation - EnemyLocation;
	const float RaycastSize = GravityGunComp->GetRayCastSize();
	if( RaycastSize < EnemyToPickUp.Size() )
	{
		return Failed();
	}

	// Add some Random Angle
	CurrentRandomAngleYaw = FMath::RandRange(-RandomAngleAroundRaycast, RandomAngleAroundRaycast);
	CurrentRandomAnglePitch = FMath::RandRange(-RandomAngleAroundRaycast, RandomAngleAroundRaycast);
	EnemyToPickUp = EnemyToPickUp.RotateAngleAxis(CurrentRandomAngleYaw, EnemyCharacter->GetActorUpVector());
	EnemyToPickUp = EnemyToPickUp.RotateAngleAxis(CurrentRandomAnglePitch, EnemyCharacter->GetActorRightVector());

	// Compute Check Location
	EnemyToPickUp.Normalize();
	const FVector CheckLocation = EnemyLocation + (EnemyToPickUp * RaycastSize );

	// Launch Raycast
	if( !GravityGunComp->AITakePickUp(EnemyLocation, CheckLocation) )
	{
		return Failed();
	}

	// Update BB Values
	BlackboardComp->SetValueAsBool(EnemyHasPickUpKey.SelectedKeyName, true);
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTask_TakePickUp::Failed()
{
	// Start timer
	if( EnemyController )
	{
		EnemyController->StartPickUpTimer(PickUpTimer);
	}

	return EBTNodeResult::Failed;
}

void UBTTask_TakePickUp::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	// At runtime, we want to display the angles
	Values.Add(FString::Printf(TEXT("Yaw Angle: %f - Pitch Angle: %f"), 
		CurrentRandomAngleYaw, CurrentRandomAnglePitch));
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
}

FString UBTTask_TakePickUp::GetStaticDescription() const
{
	FString StaticDescription("invalid");
	if( ( PickUpKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass() )
		|| ( EnemyHasPickUpKey.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass() ) )
	{
		StaticDescription = FString::Printf(TEXT("Pick Up: %s - Enemy Has Pick Up: %s\nAngle : %f - Timer: %f"),
			*PickUpKey.SelectedKeyName.ToString(), *EnemyHasPickUpKey.SelectedKeyName.ToString(),
			RandomAngleAroundRaycast, PickUpTimer);
	}

	return FString::Printf(TEXT("%s : %s"), *Super::GetStaticDescription(), *StaticDescription);
}
