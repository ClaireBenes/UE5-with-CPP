// UI
#include "UI/Menu/OptionMenuCAW.h"
#include "UI/MainCommonButtonBase.h"
#include "UI/Menu/KeyMappingCAW.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/VerticalBox.h"

// Controller
#include "Controller/MainPlayerController.h"


void UOptionMenuCAW::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind Button
	if( BIND_ExitMenu_Button )
	{
		BIND_ExitMenu_Button->OnButtonClicked.AddUniqueDynamic(this, &UOptionMenuCAW::CloseMenu);
	}

	// Bind Sliders
	if( BIND_MouseSensitivityX_Slider )
	{
		// Bind to Slider Value Event
		BIND_MouseSensitivityX_Slider->OnValueChanged.AddUniqueDynamic(this, &UOptionMenuCAW::ReceiveXSliderValue);

		// Initialize Value Displayed on the Slider
		if( PlayerController.IsValid() )
		{
			const float SensitivityX = PlayerController->GetMouseSensitivityX();
			BIND_MouseSensitivityX_Slider->SetValue(SensitivityX);
			DisplaySensitivityX(SensitivityX);
		}
	}
	if( BIND_MouseSensitivityY_Slider )
	{
		// Bind to Slider Value Event
		BIND_MouseSensitivityY_Slider->OnValueChanged.AddUniqueDynamic(this, &UOptionMenuCAW::ReceiveYSliderValue);

		// Initialize Value Displayed on the Slider
		if( PlayerController.IsValid() )
		{
			const float SensitivityY = PlayerController->GetMouseSensitivityY();
			BIND_MouseSensitivityY_Slider->SetValue(SensitivityY);
			DisplaySensitivityY(SensitivityY);
		}
	}
}

void UOptionMenuCAW::ReceiveXSliderValue(float NewValue)
{
	if( PlayerController.IsValid() )
	{
		PlayerController->SetMouseSensitivityX(NewValue);
	}

	DisplaySensitivityX(NewValue);
}

void UOptionMenuCAW::ReceiveYSliderValue(float NewValue)
{
	if( PlayerController.IsValid() )
	{
		PlayerController->SetMouseSensitivityY(NewValue);
	}

	DisplaySensitivityY(NewValue);
}

void UOptionMenuCAW::DisplaySensitivityX(float InSensitivity)
{
	if( BIND_MouseSensitivityX_Text )
	{
		BIND_MouseSensitivityX_Text->SetText(ConvertSensitivityToDisplayText(InSensitivity));
	}
}

void UOptionMenuCAW::DisplaySensitivityY(float InSensitivity)
{
	if( BIND_MouseSensitivityY_Text )
	{
		BIND_MouseSensitivityY_Text->SetText(ConvertSensitivityToDisplayText(InSensitivity));
	}
}

FText UOptionMenuCAW::ConvertSensitivityToDisplayText(float InSensitivity)
{
	float SensitivityToDisplay = InSensitivity * 100.0f;
	SensitivityToDisplay = FMath::RoundToInt(SensitivityToDisplay) * 0.01;

	// Create the display text
	FString SensitivityText = FString::SanitizeFloat(SensitivityToDisplay, 2);
	FText FinalText = FText::FromString(SensitivityText);
	return FinalText;
}
