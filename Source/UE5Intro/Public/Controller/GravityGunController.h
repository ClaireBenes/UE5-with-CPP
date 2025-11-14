#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityGunController.generated.h"

UCLASS( Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5INTRO_API UGravityGunController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGravityGunController();	
	void SetupInputComponentGravityGun(TObjectPtr<class UInputComponent> InputComponent, class APawn* InPawn);

protected:
	TWeakObjectPtr<class UGravityGunComponent> GravityGunComponent = nullptr;

// Inputs
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionTakeObject = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionThrowObject = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionChangeRaycastSize = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionAddForceMultiplier = nullptr;

protected:
	void TakeObject(const struct FInputActionValue& Value);
	void ThrowObject(const struct FInputActionValue& Value);
	void ChangeRaycastSize(const struct FInputActionValue& Value);
	void AddForceMultiplier();
// End of Inputs

};
