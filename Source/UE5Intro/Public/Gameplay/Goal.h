#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/GoalEnum.h"
#include "Goal.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoalScoredDelegate, ETeamType, TeamType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAISphereOverlapDelegate, bool, bIsOverlap, ETeamType, Team, AActor*, ActorOverlaped);

UCLASS(Abstract)
class UE5INTRO_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	AGoal(const FObjectInitializer& ObjectInitializer);
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;

// Team Score
public:
	ETeamType GetTeamType() const;

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

// Light
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPointLightComponent> PointLightComponent = nullptr;

protected:
	void UpdatePointLight();
// End of Light

// AI Sphere
protected: 
	UFUNCTION()
	void OnAIBehaviourSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnAIBehaviourSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	class USphereComponent* GetAIBehaviorCollisionSphere() const;

public:
	FAISphereOverlapDelegate OnAISphereOverlap;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<class USphereComponent> AIBehaviorCollisionSphere = nullptr;
// End of AI Sphere
};
