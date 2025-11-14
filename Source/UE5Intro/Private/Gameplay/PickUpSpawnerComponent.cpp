#include "Gameplay/PickUpSpawnerComponent.h"

#include "Gameplay/MainCharacter.h"
#include "Gameplay/GravityGun/GravityGunComponent.h"

#include "Gameplay/PickUpComponent.h"
#include "GameFramework/Actor.h"

UPickUpSpawnerComponent::UPickUpSpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPickUpSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get Character
	Character = Cast<AMainCharacter>(GetOwner());

	if( !Character.IsValid() )
	{
		return;
	}

	// Get Gravity Gun Component
	GravityGunComponent = Character->FindComponentByClass<UGravityGunComponent>();
}

void UPickUpSpawnerComponent::OnSpawnPickUp( EPickUpType PickUpType)
{
	if( !PickUpNormal || !PickUpDestroyAfterPickUp || !PickUpDestroyAfterThrow )
	{
		return;
	}

	// Initialize Spawn Variable
	FVector Location = Character->GetActorLocation() + ( Character->GetActorForwardVector() * 100 );
	FRotator Rotation = Character->GetActorRotation();
	FTransform Transform;
	FActorSpawnParameters PickUpSpawnParameters;

	switch( PickUpType )
	{
		case EPickUpType::None:
			return;
			break;

		case EPickUpType::Normal:
			NewPickUp = GetWorld()->SpawnActor<AActor>(PickUpNormal, Location, Rotation, PickUpSpawnParameters);
			break;

		case EPickUpType::DestroyAfterPickUp:
			NewPickUp = GetWorld()->SpawnActor<AActor>(PickUpDestroyAfterPickUp, Location, Rotation, PickUpSpawnParameters);
			break;

		case EPickUpType::DestroyAfterThrow:
			NewPickUp = GetWorld()->SpawnActor<AActor>(PickUpDestroyAfterThrow, Location, Rotation, PickUpSpawnParameters);
			break;

		case EPickUpType::MAX:
			return;
			break;

		default:
			break;
	}

	if( !GravityGunComponent.IsValid() )
	{
		return;
	}

	if( !GravityGunComponent->GetCurrentPickUp().IsValid() )
	{
		GravityGunComponent->TakePickUp(NewPickUp);
	}
}

