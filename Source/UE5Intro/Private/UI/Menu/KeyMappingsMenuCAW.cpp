// UI
#include "UI/Menu/KeyMappingsMenuCAW.h"
#include "UI/MainCommonButtonBase.h"
#include "UI/Menu/KeyMappingCAW.h"
#include "UI/MenuNavigationDataAsset.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/VerticalBox.h"

// Controller
#include "Controller/MainPlayerController.h"

// Input
#include "EnhancedInputSubsystems.h"

void UKeyMappingsMenuCAW::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind Button
	if( BIND_ExitMenu_Button )
	{
		BIND_ExitMenu_Button->OnButtonClicked.AddUniqueDynamic(this, &UKeyMappingsMenuCAW::CloseMenu);
	}

	// Display Mappable Keys
	DisplayKeys();
}

void UKeyMappingsMenuCAW::DisplayKeys()
{
	// Check pointer and Widget Name
	if( !BIND_KeyMappingMovement_VB || !BIND_KeyMappingAction_VB  || KeyMappingWidgetName.IsEmpty() || !PlayerController.IsValid() )
	{
		return;
	}

	// Make sure that there is nothing insode the VB
	if( (BIND_KeyMappingMovement_VB->GetChildrenCount() != 0) || (BIND_KeyMappingAction_VB->GetChildrenCount() != 0) )
	{
		return;
	}

	// Get Enhanced Subsystem
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if( !InputSubsystem )
	{
		return;
	}

	// Get Widget Template
	TSubclassOf<UCommonActivatableWidget> KeybindingWidgetTemplate = *MenuNavigationInfoDataAsset->MenuNavigationActivatableWidgetMap.Find(KeyMappingWidgetName);
	if( !KeybindingWidgetTemplate )
	{
		return;
	}

	// Get all Mappable Keys
	TArray<FEnhancedActionKeyMapping> MappableKeys = InputSubsystem->GetAllPlayerMappableActionKeyMappings();
	if( MappableKeys.IsEmpty() )
	{
		return;
	}

	// For all mappable Keys, let's create a KeyMappingCAW
	for( FEnhancedActionKeyMapping& Key : MappableKeys )
	{
		// Get Name and Display Name
		FName KeyName = Key.GetMappingName();
		FText KeyDisplayName = Key.GetDisplayName();

		// Create KeyMappingCAW
		UKeyMappingCAW* NewKeyWidget = CreateWidget<UKeyMappingCAW>(this, KeybindingWidgetTemplate);
		if( NewKeyWidget )
		{
			// Set all Key infos
			NewKeyWidget->SetInputName(KeyName);
			NewKeyWidget->SetInputDisplayName(KeyDisplayName);
			NewKeyWidget->SetInputSelector(Key);

			// Add the widget in the correct Vertical Box
			const FString KeyCategory = Key.GetDisplayCategory().ToString();
			if( KeyCategory == MovementCategoryName )
			{
				BIND_KeyMappingMovement_VB->AddChild(NewKeyWidget);
			}
			else if( KeyCategory == ActionCategoryName )
			{
				BIND_KeyMappingAction_VB->AddChild(NewKeyWidget);
			}
			else
			{
				NewKeyWidget->Destruct();
			}		
		}
	}
}
