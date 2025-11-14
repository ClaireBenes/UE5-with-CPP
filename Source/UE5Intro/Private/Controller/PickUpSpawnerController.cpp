#include "Controller/PickUpSpawnerController.h"

//Inputs
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

// Gameplay
#include "Gameplay/PickUpSpawnerComponent.h"
#include "Gameplay/PickUpComponent.h"

UPickUpSpawnerController::UPickUpSpawnerController()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPickUpSpawnerController::SetupInputComponentPickUpSpawner(TObjectPtr<class UInputComponent> InputComponent, APawn* InPawn)
{
	// Get the pickup spawner comp
	if( InPawn )
	{
		PickUpSpawnerComponent = InPawn->FindComponentByClass<UPickUpSpawnerComponent>();
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

	if( InputActionSpawnPickUpNormal )
	{
		EnhancedInputComponent->BindAction(InputActionSpawnPickUpNormal, ETriggerEvent::Triggered, this, &UPickUpSpawnerController::SpawnPickUpNormal);
	}
	if( InputActionSpawnPickUpDestroyAfterPickUp )
	{
		EnhancedInputComponent->BindAction(InputActionSpawnPickUpDestroyAfterPickUp, ETriggerEvent::Triggered, this, &UPickUpSpawnerController::SpawnPickUpDestroyAfterPickUp);
	}
	if( InputActionSpawnPickUpDestroyAfterThrow )
	{
		EnhancedInputComponent->BindAction(InputActionSpawnPickUpDestroyAfterThrow, ETriggerEvent::Triggered, this, &UPickUpSpawnerController::SpawnPickUpDestroyAfterThrow);
	}
}

void UPickUpSpawnerController::SpawnPickUpNormal(const FInputActionValue& Value)
{
	if( PickUpSpawnerComponent.IsValid() )
	{
		PickUpSpawnerComponent->OnSpawnPickUp(EPickUpType::Normal);
	}
}

void UPickUpSpawnerController::SpawnPickUpDestroyAfterPickUp(const FInputActionValue& Value)
{
	if( PickUpSpawnerComponent.IsValid() )
	{
		PickUpSpawnerComponent->OnSpawnPickUp(EPickUpType::DestroyAfterPickUp);
	}
}

void UPickUpSpawnerController::SpawnPickUpDestroyAfterThrow(const FInputActionValue& Value)
{
	if( PickUpSpawnerComponent.IsValid() )
	{
		PickUpSpawnerComponent->OnSpawnPickUp(EPickUpType::DestroyAfterThrow);
	}
}

