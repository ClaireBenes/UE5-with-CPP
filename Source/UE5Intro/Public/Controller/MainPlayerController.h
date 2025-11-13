#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


UCLASS(Abstract)
class UE5INTRO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	virtual void SetPawn(class APawn* InPawn) override;

protected:
	TWeakObjectPtr<class AMainCharacter> Character = nullptr;
	TWeakObjectPtr<class UGravityGunController> GravityGunController = nullptr;
	TWeakObjectPtr<class UScoreComponent> ScoreComponent = nullptr;
	
// Inputs
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputMappingContext> InputMappingContext = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionMove = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionLook = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionJump = nullptr;

protected:
	void MovePlayer(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void Jump();
// End of Inputs


// Mouse Sensitivity
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input|Mouse", meta = (ClampMin = "0.1", ClampMa = "3.0" ))
	float MouseSensitivityX = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input|Mouse", meta = ( ClampMin = "0.1", ClampMa = "3.0" ))
	float MouseSensitivityY = 1.0f;

public:
	virtual void AddPitchInput(float Val) override;
	virtual void AddYawInput(float Val) override;
// End of Mouse Sensitivity

// Goals Score
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionShowScore = nullptr;

protected:
	void ShowScore();
// End of Goals Score

// Pick Up In Goal
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputActionPickUpInGoal = nullptr;

protected:
	void PickUpInGoal();
// Enf of Pick Up In Goal
	
};
