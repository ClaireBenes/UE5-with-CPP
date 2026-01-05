#include "Controller/MainPlayerController.h"

// Inputs
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Gameplay
#include "Gameplay/MainCharacter.h"
#include "Controller/GravityGunController.h"
#include "Gameplay/ScoreComponent.h"
#include "Controller/PickUpSpawnerController.h"

// UI
#include "UI/Menu/BaseMenuCommonUserWidget.h"
#include "UI/MenuNavigationDataAsset.h"
#include "CommonActivatableWidget.h"

// Settings
#include "Settings/UIParametersSubsystem.h"


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
	if( InputActionPickUpInGoal )
	{
		EnhancedInputComponent->BindAction(InputActionPickUpInGoal, ETriggerEvent::Triggered, this, &AMainPlayerController::PickUpInGoal);
	}
	if( InputActionPause )
	{
		EnhancedInputComponent->BindAction(InputActionPause, ETriggerEvent::Triggered, this, &AMainPlayerController::OnPauseInputPressed);
	}
}

void AMainPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	// Get Character and its Char Move Comp
	if( !Character.IsValid() )
	{
		Character = Cast<AMainCharacter>(InPawn);

		ScoreComponent = Character->FindComponentByClass<UScoreComponent>();

		GravityGunController = FindComponentByClass<UGravityGunController>();
		if( GravityGunController.IsValid() )
		{
			GravityGunController->SetupInputComponentGravityGun(InputComponent, InPawn);
		}

		PickUpSpawnerController = FindComponentByClass<UPickUpSpawnerController>();
		if( PickUpSpawnerController.IsValid() )
		{
			PickUpSpawnerController->SetupInputComponentPickUpSpawner(InputComponent, InPawn);
		}
	}
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Load Data Asset
	UUIParametersSubsystem* UIParametersSubsystem = GEngine->GetEngineSubsystem<UUIParametersSubsystem>();

	if( UIParametersSubsystem )
	{
		MenuNavigationInfoDataAsset = UIParametersSubsystem->GetMenuNavigationInfo();
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

void AMainPlayerController::PickUpInGoal()
{
	if( ScoreComponent.IsValid() )
	{
		ScoreComponent->CountPickUpInGoal();
	}
}

void AMainPlayerController::OnPauseInputPressed()
{
	// Check Data Asset and Names
	if( !MenuNavigationInfoDataAsset.IsValid() || PauseMenuActivatableWidgetName.IsEmpty() || PauseMenuBackgroundWidgetName.IsEmpty() )
	{
		return;
	}

	// Get the right widget template for background
	TSubclassOf<UUserWidget> MenuWidgetTemplate = *MenuNavigationInfoDataAsset->MenuNavigationMap.Find(PauseMenuBackgroundWidgetName);
	if( !MenuWidgetTemplate )
	{
		return;
	}

	// Spawn Background widget and display it
	UBaseMenuCommonUserWidget* MenuWidget = CreateWidget<UBaseMenuCommonUserWidget>(this, MenuWidgetTemplate);

	if( MenuWidget )
	{
		MenuWidget->AddToViewport(0);

		// Look for the template of the Activatable Widget
		TSubclassOf<UCommonActivatableWidget> MenuActivatableWidgetTemplate = 
			*MenuNavigationInfoDataAsset->MenuNavigationActivatableWidgetMap.Find(PauseMenuActivatableWidgetName);

		if( MenuActivatableWidgetTemplate )
		{
			// Give it to the Background Widget so it can spawn it
			MenuWidget->AddWidgetOnStack(MenuActivatableWidgetTemplate);
		}

	}
}
