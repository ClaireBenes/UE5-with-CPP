#pragma once

#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUpSpawnerComponent.generated.h"


UCLASS(Abstract, Blueprintable, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ))
class UE5INTRO_API UPickUpSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPickUpSpawnerComponent();

protected:
	virtual void BeginPlay() override;		

protected:
	TWeakObjectPtr<class AMainCharacter> Character = nullptr;
	TWeakObjectPtr<class UGravityGunComponent> GravityGunComponent = nullptr;

// Inputs
public:
	void OnSpawnPickUp(EPickUpType PickUpType);
	void ShowAllPickUps();
// End of Inputs

// Spawn
public:
	void StartPickUpSpawnTimer();
	void ClearPickUpSpawnTimer();

protected:
	FTimerHandle PickUpSpawnTimerHandle;
	UPROPERTY(EditAnywhere, Category = "Pick Up|Spawn")
	float TimeToSpawn = 1.2f;
// End of Spawn

// Pick Up
protected:
	UFUNCTION()
	void OnPickUpDestroyed(EPickUpType PickUpType);

protected:
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	TSubclassOf<class AActor> PickUpNormal = nullptr;
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	TSubclassOf<class AActor> PickUpDestroyAfterPickUp = nullptr;
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	TSubclassOf<class AActor> PickUpDestroyAfterThrow = nullptr;

	TWeakObjectPtr<AActor> NewPickUp;

	UPROPERTY(EditAnywhere, Category = "Pick Up|Amount", meta = ( ClampMin = "1", ClampMax = "20" ))
	unsigned int MaxPickUps = 12;
	UPROPERTY(EditAnywhere, Category = "Pick Up|Amount", meta = ( ClampMin = "1", ClampMax = "20" ))
	unsigned int MaxNormalPickUp = 5;
	UPROPERTY(EditAnywhere, Category = "Pick Up|Amount", meta = ( ClampMin = "1", ClampMax = "20" ))
	unsigned int MaxDestroyAfterPickUp = 4;
	UPROPERTY(EditAnywhere, Category = "Pick Up|Amount", meta = ( ClampMin = "1", ClampMax = "20" ))
	unsigned int MaxDestroyAfterThrowsPickUps = 5;

	unsigned int PickUps = 0;
	unsigned int NormalPickUps = 0;
	unsigned int DestroyAfterPickUps = 0;
	unsigned int DestroyAfterThrowsPickUps = 0;
// End of Pick Up
};
