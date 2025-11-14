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

	UPROPERTY(EditAnywhere, Category = "Pick Up", meta = ( ClampMin = "1", ClampMax = "20" ))
	unsigned int MaxPickUps = 12;
	UPROPERTY(EditAnywhere, Category = "Pick Up", meta = ( ClampMin = "1", ClampMax = "20" ))
	unsigned int MaxNormalPickUp = 5;
	UPROPERTY(EditAnywhere, Category = "Pick Up", meta = ( ClampMin = "1", ClampMax = "20" ))
	unsigned int MaxDestroyAfterPickUp = 4;
	UPROPERTY(EditAnywhere, Category = "Pick Up", meta = ( ClampMin = "1", ClampMax = "20" ))
	unsigned int MaxDestroyAfterThrowsPickUps = 5;

	unsigned int PickUps = 0;
	unsigned int NormalPickUps = 0;
	unsigned int DestroyAfterPickUps = 0;
	unsigned int DestroyAfterThrowsPickUps = 0;
// End of Pick Up

//Inputs
public:
	UFUNCTION()
	void OnSpawnPickUp(EPickUpType PickUpType);
	void ShowAllPickUps();
// end of Inputs
};
