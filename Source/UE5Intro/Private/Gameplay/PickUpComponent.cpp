#include "Gameplay/PickUpComponent.h"

UPickUpComponent::UPickUpComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPickUpComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearDestructionTimer();
	Super::EndPlay(EndPlayReason);
}

EPickUpType UPickUpComponent::GetPickUpType() const
{
	return PickUpStruct.PickUpType;
}

void UPickUpComponent::StartPickUpDestructionTimer()
{
	// Make sure we need to start the timer
	if( ( PickUpStruct.PickUpType != EPickUpType::DestroyAfterPickUp ) && ( PickUpStruct.PickUpType != EPickUpType::DestroyAfterThrow ) )
	{
		return;
	}

	// Get time
	float TimeToDestroy = PickUpStruct.DestructionTime;

	// Prepare and start timer
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(PickUpDestructionTimerHandle);
	TimerManager.SetTimer(PickUpDestructionTimerHandle, this, &UPickUpComponent::DestroyPickUp, TimeToDestroy, false);
}

void UPickUpComponent::ClearDestructionTimer()
{
	// Clear timer
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(PickUpDestructionTimerHandle);
}

void UPickUpComponent::DestroyPickUp()
{
	ClearDestructionTimer();

	// Broadcast event
	OnPickDestroyed.Broadcast();
	OnPickUpTypeDestroyed.Broadcast(PickUpStruct.PickUpType);

	// Destroy the pick up
	// I'm destroying my parent. The components will be destroyed first, then the actor itself will be destroy
	GetOwner()->Destroy();
}

