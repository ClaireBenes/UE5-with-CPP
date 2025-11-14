#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UENUM()
enum class ETeamType : uint8
{
	None UMETA(Hidden),
	Blue,
	Red,
	MAX UMETA(Hidden),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoalScoredDelegate, ETeamType, TeamType);

UCLASS(Abstract)
class UE5INTRO_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	AGoal(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;

// Team Score
public:
	ETeamType GetTeamType();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	ETeamType TeamType = ETeamType::None;
// End of Team Score

// Collision Box
public:
	FOnGoalScoredDelegate OnGoalScored;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> CollisionBox = nullptr;

	unsigned int Score = 0;

protected:
	UFUNCTION()
	void OnGoalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// end of Collision Box

// Pick Up In Goal
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Goal")
	bool bUseOverlappingActorsFunction = false;

	UPROPERTY(EditDefaultsOnly, Category = "Goal")
	TEnumAsByte<ETraceTypeQuery>GoalTraceChannel;

public:
	unsigned int CountPickUpInGoal();
// End of Pick Up In Goal
};
