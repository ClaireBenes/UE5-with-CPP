// UI
#include "UI/Menu/KeyMappingCAW.h"
#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"
#include "Framework/Commands/InputChord.h"

// Controller
#include "Controller/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UKeyMappingCAW::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind the Key Selector
	if( BIND_InputSelector )
	{
		BIND_InputSelector->OnKeySelected.AddUniqueDynamic(this, &UKeyMappingCAW::OnKeySelected);
	}
}

void UKeyMappingCAW::SetInputName(FName InName)
{
	InputName = InName;
}

void UKeyMappingCAW::SetInputDisplayName(FText InDisplayName)
{
	if( BIND_InputDisplayName_Text )
	{
		BIND_InputDisplayName_Text->SetText(InDisplayName);
	}
}

void UKeyMappingCAW::SetInputSelector(FEnhancedActionKeyMapping& GivenKey)
{
	if( BIND_InputSelector )
	{
		BIND_InputSelector->SetSelectedKey(GivenKey.Key);
		DisplayKey = GivenKey;
	}
}

void UKeyMappingCAW::OnKeySelected(FInputChord SelectedKey)
{
	// Send Selected Key to the Player Controller
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if( PlayerController )
	{
		PlayerController->OnUpdateMappableKey(InputName, SelectedKey.Key);
	}
}
