#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityGunComponent.generated.h"


UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5INTRO_API UGravityGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGravityGunComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

protected:
	TWeakObjectPtr<class AMainCharacter> Character = nullptr;
	TWeakObjectPtr<class APlayerCameraManager> CharacterCameraManager = nullptr;

//Inputs
public:
	void OnTakeObjectInputPressed();
	void OnThrowObjectInputPressed();
	void OnThrowObjectInputReleased();
	void OnChangeRaycastSize(const float Value);
	void OnAddForceMultiplier();
//End of Inputs

// Collision
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun")
	TEnumAsByte<ETraceTypeQuery> GravityGunTraceChannel;
	ECollisionChannel GravityGunCollisionChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun|Raycast", meta = ( ClampMin = "100.0", ClampMax = "1000.0", Units = "Centimeters" ))
	float RaycastMaxSize = 1000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun|Raycast", meta = ( ClampMin = "100.0", ClampMax = "1000.0", Units = "Centimeters" ))
	float RaycastMinSize = 100.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun|Raycast", meta = ( Units = "Centimeters" ))
	float RaycastSize = 500.0f;
// End of Collision

// Debug
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun|Debug")
	bool bDrawDebugRaycast = false;
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun|Debug", meta = ( EditCondition = "bDrawDebugRaycast", EditConditionHides, Units = "Seconds" ))
	float DrawDebugTime = 2.0f;

// End of Debug

// Pick Up
protected:
	TWeakObjectPtr<AActor> CurrentPickUp = nullptr;
	TWeakObjectPtr<class UPickUpComponent> CurrentPickUpComponent = nullptr;
	TWeakObjectPtr<class UStaticMeshComponent> CurrentPickUpStaticMesh = nullptr;

	FName PreviousCollisionProfileName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun", meta = ( ClampMin = "100.0", ClampMax = "1000.0" ))
	float PickUpHoldDistance = 150.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun|Throw", meta = ( ClampMin = "100.0", ClampMax = "10000.0" ))
	float PickUpMaxThrowForce = 5000.0;
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun|Throw", meta = ( ClampMin = "100.0", ClampMax = "10000.0" ))
	float PickUpMinThrowForce = 1000;
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun|Throw")
	float PickUpForceMultiplier = 5.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun|Throw", meta = ( ClampMin = "0.0", ClampMax = "10.0" ))
	float PickUpTimeToReachMaxForce = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Gravity Gun")
	FVector PickUpMaxAngularForce = FVector(1000.0f, 1000.0f, 1000.0f);

	float PickUpThrowForce = PickUpMinThrowForce;
	float PickUpCurrentForceMultiplier = 1.0f;
	float PickUpCurrentThrowTime = 0.0f;

	bool bPickUpHasForceMultiplier = false;

protected:
	void UpdatePickUpLocation();
	void ReleasePickUp(bool bThrow = false);

	UFUNCTION()
	void OnHoldPickUpDestroy();
// End of Pick Up

};
