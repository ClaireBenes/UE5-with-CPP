#include "Gameplay/GravityGun/GravityGunComponent.h"

#include "Gameplay/MainCharacter.h"
#include "Gameplay/PickUpComponent.h"
#include "Camera/PlayerCameraManager.h"

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

UGravityGunComponent::UGravityGunComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGravityGunComponent::BeginPlay()
{
	Super::BeginPlay();	

	// Get Camera Manager
	CharacterCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	// Get Character
	Character = Cast<AMainCharacter>(GetOwner());

	// Convert collision channel
	GravityGunCollisionChannel = UEngineTypes::ConvertToCollisionChannel(GravityGunTraceChannel);
}


void UGravityGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdatePickUpLocation();
}

void UGravityGunComponent::OnTakeObjectInputPressed()
{
	// Check Camera & Character
	if( !CharacterCameraManager.IsValid() || !Character.IsValid() )
	{
		return;
	}

	// If we already have a pick up in hand, let's release it
	if( CurrentPickUp.IsValid() )
	{
		ReleasePickUp();
		return;
	}

	// Compute Raycast Location
	const FVector RaycastStart = CharacterCameraManager->GetCameraLocation();
	const FVector RaycastEnd = RaycastStart + ( CharacterCameraManager->GetActorForwardVector() * RaycastSize );

	// Prepare Raycast Structs
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character.Get());
	FHitResult HitResult;

	// Launch debug raycast
#if !UE_BUILD_SHIPPING
	if( bDrawDebugRaycast )
	{
		DrawDebugLine(GetWorld(), RaycastStart, RaycastEnd, FColor::Red, false, DrawDebugTime, 0, 1.0f);
	}
#endif

	// Launch the raycast
	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, RaycastStart, RaycastEnd, GravityGunCollisionChannel, Params);
	if( !bHit )
	{
		return;
	}

	const FString HitActorName = UKismetSystemLibrary::GetDisplayName(HitResult.GetActor());

	// Get Pick Up
	CurrentPickUp = HitResult.GetActor();
	TakePickUp(CurrentPickUp);
}

void UGravityGunComponent::OnThrowObjectInputPressed()
{
	// Add force while pressing
	PickUpCurrentThrowTime += GetWorld()->GetDeltaSeconds();
	float Alpha = FMath::Clamp(PickUpCurrentThrowTime / PickUpTimeToReachMaxForce, 0.0f, 1.0f);

	PickUpThrowForce = FMath::Lerp(PickUpMinThrowForce, PickUpMaxThrowForce, Alpha);
	PickUpThrowForce = FMath::Clamp(PickUpThrowForce, PickUpMinThrowForce, PickUpMaxThrowForce);
}

void UGravityGunComponent::OnThrowObjectInputReleased()
{
	// Throw the pick up if we have one
	if( CurrentPickUp.IsValid() )
	{
		ReleasePickUp(true);
	}
}


void UGravityGunComponent::UpdatePickUpLocation()
{
	// Check pointers
	if( !CurrentPickUp.IsValid() || !CharacterCameraManager.IsValid() )
	{
		return;
	}

	// Compute and apply new transform
	const FRotator CameraRotation = CharacterCameraManager->GetCameraRotation();
	const FVector CameraLocation = CharacterCameraManager->GetCameraLocation();
	const FVector CameraForward = CharacterCameraManager->GetActorForwardVector();

	const FVector NewPickUpLocation = CameraLocation + ( CameraForward * PickUpHoldDistance );
	CurrentPickUp->SetActorLocationAndRotation(NewPickUpLocation, CameraRotation);
}

void UGravityGunComponent::ReleasePickUp(bool bThrow )
{
	// Unbind from the destruction event if necessary
	if( CurrentPickUpComponent.IsValid() && ( CurrentPickUpComponent->GetPickUpType() == EPickUpType::DestroyAfterPickUp ) )
	{
		CurrentPickUpComponent->OnPickDestroyed.RemoveDynamic(this, &UGravityGunComponent::OnHoldPickUpDestroy);
	}

	if( CurrentPickUpStaticMesh.IsValid() )
	{
		// Enable back physics and collision
		CurrentPickUpStaticMesh->SetCollisionProfileName(PreviousCollisionProfileName);
		CurrentPickUpStaticMesh->SetSimulatePhysics(true);

		// Throw the pick up
		if( bThrow && CharacterCameraManager.IsValid() )
		{
			// Add Impulse 
			const FVector Impulse = CharacterCameraManager->GetActorForwardVector() * PickUpThrowForce;
			CurrentPickUpStaticMesh->AddImpulse(Impulse * 10 * PickUpCurrentForceMultiplier);

			// Add Angular Impulse
			const FVector AngularImpulse = FVector(
				FMath::RandRange(-PickUpMaxAngularForce.X, PickUpMaxAngularForce.X), 
				FMath::RandRange(-PickUpMaxAngularForce.Y, PickUpMaxAngularForce.Y), 
				FMath::RandRange(-PickUpMaxAngularForce.Z, PickUpMaxAngularForce.Z));
			CurrentPickUpStaticMesh->AddAngularImpulseInDegrees(AngularImpulse * 100 );
		}
	}

	// Check if destruction timer is required
	if( CurrentPickUpComponent.IsValid() && ( CurrentPickUpComponent->GetPickUpType() == EPickUpType::DestroyAfterThrow ))
	{
		CurrentPickUpComponent->StartPickUpDestructionTimer();
	}

	// Clear Pointers
	CurrentPickUpStaticMesh = nullptr;
	CurrentPickUpComponent = nullptr;
	CurrentPickUp = nullptr;

	PickUpThrowForce = PickUpMinThrowForce;
	PickUpCurrentThrowTime = 0.0f;
}

void UGravityGunComponent::OnHoldPickUpDestroy()
{
	ReleasePickUp();
}

void UGravityGunComponent::OnChangeRaycastSize(const float Value)
{
	RaycastSize = FMath::Clamp(RaycastSize + ( RaycastSize * Value * 10 ), RaycastMinSize, RaycastMaxSize);
}

void UGravityGunComponent::OnAddForceMultiplier()
{
	bPickUpHasForceMultiplier = !bPickUpHasForceMultiplier;

	//GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, FString::Printf(TEXT("Force: %d"), bPickUpHasForceMultiplier));

	if( bPickUpHasForceMultiplier )
	{
		PickUpCurrentForceMultiplier = PickUpForceMultiplier;
	}
	else
	{
		PickUpCurrentForceMultiplier = 1.0f;
	}
}

TWeakObjectPtr<AActor> UGravityGunComponent::GetCurrentPickUp()
{
	return CurrentPickUp;
}

void UGravityGunComponent::TakePickUp(TWeakObjectPtr<AActor> PickUp)
{
	// Get Pick Up
	if( !PickUp.IsValid() )
	{
		return;
	}

	CurrentPickUp = PickUp;

	// Get Pick Up Component
	CurrentPickUpComponent = CurrentPickUp->FindComponentByClass<UPickUpComponent>();
	if( !CurrentPickUpComponent.IsValid() )
	{
		return;
	}

	// Get Pick Up Static Mesh
	CurrentPickUpStaticMesh = CurrentPickUp->FindComponentByClass<UStaticMeshComponent>();
	if( !CurrentPickUpStaticMesh.IsValid() )
	{
		return;
	}

	// Disable its physics
	CurrentPickUpStaticMesh->SetSimulatePhysics(false);

	// Update Collision Profile
	PreviousCollisionProfileName = CurrentPickUpStaticMesh->GetCollisionProfileName();
	CurrentPickUpStaticMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	// Check Pick Up Type
	switch( CurrentPickUpComponent->GetPickUpType() )
	{
		case EPickUpType::DestroyAfterPickUp:
			// Launch the timer
			CurrentPickUpComponent->StartPickUpDestructionTimer();

			// Bind to the destroy event
			CurrentPickUpComponent->OnPickDestroyed.AddUniqueDynamic(this, &UGravityGunComponent::OnHoldPickUpDestroy);
			break;

		case EPickUpType::DestroyAfterThrow:
			// Clear the timer so it doesn't disapear from our hands
			CurrentPickUpComponent->ClearDestructionTimer();
			break;

		default:
			break;
	}
}



