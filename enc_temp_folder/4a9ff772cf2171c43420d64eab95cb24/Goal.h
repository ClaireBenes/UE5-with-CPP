#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UCLASS(Abstract)
class UE5INTRO_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	AGoal(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

// Collision Box
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> CollisionBox = nullptr;

	unsigned int Score = 0;
// end of Collision Box
};
