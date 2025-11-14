#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUpSpawnerController.generated.h"


UCLASS(Abstract, Blueprintable, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ))
class UE5INTRO_API UPickUpSpawnerController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPickUpSpawnerController();	
	void SetupInputComponentPickUpSpawner(TObjectPtr<class UInputComponent> InputComponent, class APawn* InPawn);

protected:
	TWeakObjectPtr<class UPickUpSpawnerComponent> PickUpSpawnerComponent = nullptr;

// Inputs
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionSpawnPickUpNormal = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionSpawnPickUpDestroyAfterPickUp = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionSpawnPickUpDestroyAfterThrow = nullptr;

protected:
	void SpawnPickUpNormal(const struct FInputActionValue& Value);
	void SpawnPickUpDestroyAfterPickUp(const struct FInputActionValue& Value);
	void SpawnPickUpDestroyAfterThrow(const struct FInputActionValue& Value);
// End of Inputs
};
