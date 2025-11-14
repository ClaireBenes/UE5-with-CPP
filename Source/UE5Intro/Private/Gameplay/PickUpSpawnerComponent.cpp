#include "Gameplay/PickUpSpawnerComponent.h"

#include "Kismet/GameplayStatics.h"

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

	// Get All Pick Ups
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);

	for( int i = 0; i < Actors.Num(); i++ )
	{
		// Get Pick Up Component
		TWeakObjectPtr< UPickUpComponent> PickUpComponent = Actors[i]->GetComponentByClass< UPickUpComponent>();
		if( PickUpComponent.IsValid() )
		{
			PickUpComponent->OnPickUpTypeDestroyed.AddUniqueDynamic(this, &UPickUpSpawnerComponent::OnPickUpDestroyed);

			// Switch on Pick Up Type to increase the amount of each Pick Up
			EPickUpType PickUpType = PickUpComponent->GetPickUpType();
			switch( PickUpType )
			{
				case EPickUpType::None:
					break;

				case EPickUpType::Normal:
					NormalPickUps++;
					break;

				case EPickUpType::DestroyAfterPickUp:
					DestroyAfterPickUps++;
					break;

				case EPickUpType::DestroyAfterThrow:
					DestroyAfterThrowsPickUps++;
					break;

				case EPickUpType::MAX:
					break;

				default:
					break;
			}

			// Increase Overall Number of Pick Up
			PickUps++;
		}
	}
}

void UPickUpSpawnerComponent::StartPickUpSpawnTimer()
{
	// Prepare and start timer
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(PickUpSpawnTimerHandle);

	TimerManager.SetTimer(PickUpSpawnTimerHandle, this, &UPickUpSpawnerComponent::ClearPickUpSpawnTimer, TimeToSpawn, false);
}

void UPickUpSpawnerComponent::ClearPickUpSpawnTimer()
{
	// Clear timer
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(PickUpSpawnTimerHandle);
}

void UPickUpSpawnerComponent::OnPickUpDestroyed(EPickUpType PickUpType)
{
	// Switch on Pick Up Type to decrease the amount of each Pick Up
	switch( PickUpType )
	{
		case EPickUpType::None:
			break;

		case EPickUpType::Normal:
			NormalPickUps--;
			break;

		case EPickUpType::DestroyAfterPickUp:
			DestroyAfterPickUps--;
			break;

		case EPickUpType::DestroyAfterThrow:
			DestroyAfterThrowsPickUps--;
			break;

		case EPickUpType::MAX:
			break;

		default:
			break;
	}

	// Decrease Overall Number of Pick Up
	PickUps--;
	UE_LOG(LogTemp, Log, TEXT("Now, %d Pick Ups on the map"), PickUps);
}

void UPickUpSpawnerComponent::OnSpawnPickUp( EPickUpType PickUpType)
{
	// Check PickUp
	if( !PickUpNormal || !PickUpDestroyAfterPickUp || !PickUpDestroyAfterThrow )
	{
		return;
	}

	// Check amount of Pick Ups
	if( PickUps >= MaxPickUps )
	{
		UE_LOG(LogTemp, Log, TEXT("Max Amount of Pick Ups on the map"));
		return;
	}

	// Check Spawn Timer is available
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if( TimerManager.IsTimerActive(PickUpSpawnTimerHandle) )
	{
		float TimeRemaining = TimerManager.GetTimerRemaining(PickUpSpawnTimerHandle);
		UE_LOG(LogTemp, Log, TEXT("Wait %f seconds to be able to spawn again"), TimeRemaining);
		return;
	}

	// Initialize Spawn Variable
	FVector Location = Character->GetActorLocation() + ( Character->GetActorForwardVector() * 100 );
	FRotator Rotation = Character->GetActorRotation();
	FTransform Transform;
	FActorSpawnParameters PickUpSpawnParameters;

	// Switch on Pick Up type to spawn correct Actor
	switch( PickUpType )
	{
		case EPickUpType::None:
			return;
			break;

		case EPickUpType::Normal:
			if( NormalPickUps >= MaxNormalPickUp )
			{
				UE_LOG(LogTemp, Log, TEXT("Max Amount of Normal Pick Ups on the map"));
				return;
			}

			NewPickUp = GetWorld()->SpawnActor<AActor>(PickUpNormal, Location, Rotation, PickUpSpawnParameters);
			NormalPickUps++;
			break;

		case EPickUpType::DestroyAfterPickUp:
			if( DestroyAfterPickUps >= MaxDestroyAfterPickUp )
			{
				UE_LOG(LogTemp, Log, TEXT("Max Amount of DestroyAfterPickUp Pick Ups on the map"));
				return;
			}

			NewPickUp = GetWorld()->SpawnActor<AActor>(PickUpDestroyAfterPickUp, Location, Rotation, PickUpSpawnParameters);
			DestroyAfterPickUps++;
			break;

		case EPickUpType::DestroyAfterThrow:
			if( DestroyAfterThrowsPickUps >= MaxDestroyAfterThrowsPickUps )
			{
				UE_LOG(LogTemp, Log, TEXT("Max Amount of DestroyAfterThrow Pick Ups on the map"));
				return;
			}

			NewPickUp = GetWorld()->SpawnActor<AActor>(PickUpDestroyAfterThrow, Location, Rotation, PickUpSpawnParameters);
			DestroyAfterThrowsPickUps++;
			break;

		case EPickUpType::MAX:
			return;
			break;

		default:
			break;
	}

	// Increase Overall Pick Up Amounts
	PickUps++;
	StartPickUpSpawnTimer();
	UE_LOG(LogTemp, Log, TEXT("Spawning new Pick Up"));

	// Get Pick Up Component
	TWeakObjectPtr< UPickUpComponent> PickUpComponent = NewPickUp->GetComponentByClass< UPickUpComponent>();
	if( PickUpComponent.IsValid() )
	{
		// Bind to destroy event
		PickUpComponent->OnPickUpTypeDestroyed.AddUniqueDynamic(this, &UPickUpSpawnerComponent::OnPickUpDestroyed);
	}

	// Check Gravity Gun Component
	if( !GravityGunComponent.IsValid() )
	{
		return;
	}

	// Check Current Pick Up of Gun Component validity
	if( !GravityGunComponent->GetCurrentPickUp().IsValid() )
	{
		// Place Pick Up in Player Hands
		GravityGunComponent->TakePickUp(NewPickUp);
	}
}

void UPickUpSpawnerComponent::ShowAllPickUps()
{
	UE_LOG(LogTemp, Log, TEXT("=== Current Pick Ups ==="));
	UE_LOG(LogTemp, Log, TEXT("Amount of Normal Pick Up : %d"), NormalPickUps);
	UE_LOG(LogTemp, Log, TEXT("Amount of DestroyAfterPickUps Pick Up : %d"), DestroyAfterPickUps);
	UE_LOG(LogTemp, Log, TEXT("Amount of DestroyAfterThrows Pick Up : %d"), DestroyAfterThrowsPickUps);
	UE_LOG(LogTemp, Log, TEXT("Amount of Overall Pick Up : %d"), PickUps);
}

