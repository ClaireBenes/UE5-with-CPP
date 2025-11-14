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

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);

	for( int i = 0; i < Actors.Num(); i++ )
	{
		TWeakObjectPtr< UPickUpComponent> PickUpComponent = Actors[i]->GetComponentByClass< UPickUpComponent>();
		if( PickUpComponent.IsValid() )
		{
			PickUpComponent->OnPickUpTypeDestroyed.AddUniqueDynamic(this, &UPickUpSpawnerComponent::OnPickUpDestroyed);

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

			PickUps++;
		}
	}
}

void UPickUpSpawnerComponent::OnPickUpDestroyed(EPickUpType PickUpType)
{
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

	PickUps--;
	UE_LOG(LogTemp, Log, TEXT("Now, %d Pick Ups on the map"), PickUps);
}

void UPickUpSpawnerComponent::OnSpawnPickUp( EPickUpType PickUpType)
{
	if( !PickUpNormal || !PickUpDestroyAfterPickUp || !PickUpDestroyAfterThrow )
	{
		return;
	}

	if( PickUps >= MaxPickUps )
	{
		UE_LOG(LogTemp, Log, TEXT("Max Amount of Pick ups on the map"));
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
			if( NormalPickUps >= MaxNormalPickUp )
			{
				return;
			}

			NewPickUp = GetWorld()->SpawnActor<AActor>(PickUpNormal, Location, Rotation, PickUpSpawnParameters);
			NormalPickUps++;
			break;

		case EPickUpType::DestroyAfterPickUp:
			if( DestroyAfterPickUps >= MaxDestroyAfterPickUp )
			{
				return;
			}

			NewPickUp = GetWorld()->SpawnActor<AActor>(PickUpDestroyAfterPickUp, Location, Rotation, PickUpSpawnParameters);
			DestroyAfterPickUps++;
			break;

		case EPickUpType::DestroyAfterThrow:
			if( DestroyAfterThrowsPickUps >= MaxDestroyAfterThrowsPickUps )
			{
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

	TWeakObjectPtr< UPickUpComponent> PickUpComponent = NewPickUp->GetComponentByClass< UPickUpComponent>();
	PickUpComponent->OnPickUpTypeDestroyed.AddUniqueDynamic(this, &UPickUpSpawnerComponent::OnPickUpDestroyed);
	PickUps++;

	if( !GravityGunComponent.IsValid() )
	{
		return;
	}

	if( !GravityGunComponent->GetCurrentPickUp().IsValid() )
	{
		GravityGunComponent->TakePickUp(NewPickUp);
	}
}

void UPickUpSpawnerComponent::ShowAllPickUps()
{
	UE_LOG(LogTemp, Log, TEXT("=== Current Pick Ups ==="));
	UE_LOG(LogTemp, Log, TEXT("Amount of normal Pick Up : %d"), NormalPickUps);
	UE_LOG(LogTemp, Log, TEXT("Amount of DestroyAfterPickUps Pick Up : %d"), DestroyAfterPickUps);
	UE_LOG(LogTemp, Log, TEXT("Amount of DestroyAfterThrows Pick Up : %d"), DestroyAfterThrowsPickUps);
	UE_LOG(LogTemp, Log, TEXT("Amount of overall Pick Up : %d"), PickUps);
}

