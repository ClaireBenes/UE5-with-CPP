#include "Controller/GravityGunController.h"

//Inputs
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

// Gameplay
#include "Gameplay/GravityGun/GravityGunComponent.h"
#include "GameFramework/Pawn.h"

UGravityGunController::UGravityGunController()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGravityGunController::SetupInputComponentGravityGun(TObjectPtr<class UInputComponent> InputComponent, class APawn* InPawn)
{
	// Get the gravity gun comp
	if( InPawn )
	{
		GravityGunComponent = InPawn->FindComponentByClass<UGravityGunComponent>();
	}

	if( !InputComponent )
	{
		return;
	}

	// Cast the old InputComponent to its Enhanced Version
	UEnhancedInputComponent* EnhancedInputComponent = Cast< UEnhancedInputComponent>(InputComponent);
	if( !EnhancedInputComponent )
	{
		return;
	}

	if( InputActionTakeObject )
	{
		EnhancedInputComponent->BindAction(InputActionTakeObject, ETriggerEvent::Triggered, this, &UGravityGunController::TakeObject);
	}
	if( InputActionThrowObject )
	{
		EnhancedInputComponent->BindAction(InputActionThrowObject, ETriggerEvent::Triggered, this, &UGravityGunController::ThrowObject);
	}
	if( InputActionChangeRaycastSize )
	{
		EnhancedInputComponent->BindAction(InputActionChangeRaycastSize, ETriggerEvent::Triggered, this, &UGravityGunController::ChangeRaycastSize);
	}
	if( InputActionAddForceMultiplier )
	{
		EnhancedInputComponent->BindAction(InputActionAddForceMultiplier, ETriggerEvent::Triggered, this, &UGravityGunController::AddForceMultiplier);
	}
}

void UGravityGunController::TakeObject(const FInputActionValue& Value)
{
	if( GravityGunComponent.IsValid() )
	{
		GravityGunComponent->OnTakeObjectInputPressed();
	}
}

void UGravityGunController::ThrowObject(const FInputActionValue& Value)
{
	if( GravityGunComponent.IsValid() )
	{
		const float PressedValue = Value.Get<float>();
		if( PressedValue == 1 )
		{
			GravityGunComponent->OnThrowObjectInputPressed();
		}
		if( PressedValue == 0 )
		{
			GravityGunComponent->OnThrowObjectInputReleased();
		}
	}
}

void UGravityGunController::ChangeRaycastSize(const FInputActionValue& Value)
{
	if( GravityGunComponent.IsValid() )
	{
		// Get Movement value
		const float SizeValue = Value.Get<float>();

		GravityGunComponent->OnChangeRaycastSize(SizeValue);		
	}
}

void UGravityGunController::AddForceMultiplier()
{
	if( GravityGunComponent.IsValid() )
	{
		GravityGunComponent->OnAddForceMultiplier();
	}
}

