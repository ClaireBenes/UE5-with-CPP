#pragma once

#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUpSpawnerComponent.generated.h"

class UPickUpComponent;


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

// Pick Up
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	TSubclassOf<class AActor> PickUpNormal = nullptr;
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	TSubclassOf<class AActor> PickUpDestroyAfterPickUp = nullptr;
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	TSubclassOf<class AActor> PickUpDestroyAfterThrow = nullptr;
// End of Pick Up

//Inputs
public:
	UFUNCTION()
	void OnSpawnPickUp(EPickUpType PickUpType);
// end of Inputs
};
