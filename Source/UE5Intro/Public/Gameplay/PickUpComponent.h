#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUpComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUpDestroyDelegate);

UENUM()
enum class EPickUpType : uint8
{
	None UMETA(Hidden),
	Normal,
	DestroyAfterPickUp,
	DestroyAfterThrow,
	MAX UMETA(Hidden),
};

USTRUCT(BlueprintType)
struct FPickUpStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPickUpType PickUpType = EPickUpType::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = ( EditCondition = "(PickUpType == EPickUpType::DestroyAfterPickUp) || (PickUpType == EPickUpType::DestroyAfterThrow)",
		EditConditionHides, Units = "Seconds" ))
	float DestructionTime = 3.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUpTypeDestroyDelegate, EPickUpType, CurrentPickUpType);

UCLASS(ClassGroup = ( "Pick Up" ), meta = ( BlueprintSpawnableComponent ))
class UE5INTRO_API UPickUpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPickUpComponent();	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	EPickUpType GetPickUpType() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pick Up")
	FPickUpStruct PickUpStruct;

// Destruction
protected:
	FTimerHandle PickUpDestructionTimerHandle;

public:
	FOnPickUpDestroyDelegate OnPickDestroyed;
	FOnPickUpTypeDestroyDelegate OnPickUpTypeDestroyed;

public:
	void StartPickUpDestructionTimer();
	void ClearDestructionTimer();
	void DestroyPickUp();
// End of Destruction
};
