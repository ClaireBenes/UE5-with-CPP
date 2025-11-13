#include "Controller/MainPlayerController.h"

// Inputs
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//Gameplay
#include "Gameplay/MainCharacter.h"
#include "Controller/GravityGunController.h"
#include "Gameplay/ScoreComponent.h"


void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Get Enhanced Subsystem
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if( !InputSubsystem )
	{
		return;
	}

	// Assign our Input Mapping Context
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	// Cast the old InputComponent to its Enhanced Version
	UEnhancedInputComponent* EnhancedInputComponent = Cast< UEnhancedInputComponent>(InputComponent);
	if( !EnhancedInputComponent )
	{
		return;
	}

	if( InputActionMove )
	{
		EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &AMainPlayerController::MovePlayer);
	}
	if( InputActionLook )
	{
		EnhancedInputComponent->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &AMainPlayerController::Look);
	}
	if( InputActionJump )
	{
		EnhancedInputComponent->BindAction(InputActionJump, ETriggerEvent::Triggered, this, &AMainPlayerController::Jump);
	}
	if( InputActionShowScore)
	{
		EnhancedInputComponent->BindAction(InputActionShowScore, ETriggerEvent::Triggered, this, &AMainPlayerController::ShowScore);
	}
}

void AMainPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	// Get Character and its Char Move Comp
	if( !Character.IsValid() )
	{
		Character = Cast<AMainCharacter>(InPawn);

		GravityGunController = FindComponentByClass<UGravityGunController>();
		if( GravityGunController.IsValid() )
		{
			GravityGunController->SetupInputComponentGravityGun(InputComponent, InPawn);
		}
	}
}

void AMainPlayerController::MovePlayer(const struct FInputActionValue& Value)
{
	// Check Character
	if( !Character.IsValid() )
	{
		return;
	}

	// Get Movement value
	const FVector2D MoveValue = Value.Get<FVector2D>();

	//Check Forward Direction
	if( MoveValue.Y )
	{	
		Character->AddMovementInput(Character->GetActorForwardVector(), MoveValue.Y);
	}
	// Check Right Direction
	if( MoveValue.X )
	{
		Character->AddMovementInput(Character->GetActorRightVector(), MoveValue.X);
	}
}

void AMainPlayerController::Look(const FInputActionValue& Value)
{
	// Check Character
	if( !Character.IsValid() )
	{
		return;
	}

	// Get Look value
	const FVector2D LookValue = Value.Get<FVector2D>();

	// Yaw Axis (horizontal)
	if( LookValue.X )
	{
		Character->AddControllerYawInput(LookValue.X);
	}
	// Pitch Axis (vertical)
	if( LookValue.Y )
	{
		Character->AddControllerPitchInput(-LookValue.Y);
	}
}

void AMainPlayerController::Jump()
{
	// Check Character
	if( !Character.IsValid() )
	{
		return;
	}

	Character->Jump();
}

void AMainPlayerController::ShowScore()
{
	ScoreComponent = Character->FindComponentByClass<UScoreComponent>();
	if( ScoreComponent.IsValid() )
	{
		ScoreComponent->ShowGoalsScore();
	}
}

void AMainPlayerController::AddPitchInput(float Val)
{
	Super::AddPitchInput(Val * MouseSensitivityY);
}

void AMainPlayerController::AddYawInput(float Val)
{
	Super::AddYawInput(Val * MouseSensitivityX);
}
