#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/BaseCommonActivatableWidget.h"
#include "OptionMenuCAW.generated.h"


UCLASS(Abstract)
class UE5INTRO_API UOptionMenuCAW : public UBaseCommonActivatableWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

// Button
protected:
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_ExitMenu_Button = nullptr;
// End of Button

//Mouse Sensitivity
protected:
	UFUNCTION()
	void ReceiveXSliderValue(float NewValue);
	UFUNCTION()
	void ReceiveYSliderValue(float NewValue);

	void DisplaySensitivityX(float InSensitivity);
	void DisplaySensitivityY(float InSensitivity);

	FText ConvertSensitivityToDisplayText(float InSensitivity);

protected:
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class USlider> BIND_MouseSensitivityX_Slider = nullptr;
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class USlider> BIND_MouseSensitivityY_Slider = nullptr;

	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UTextBlock> BIND_MouseSensitivityX_Text = nullptr;;
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UTextBlock> BIND_MouseSensitivityY_Text = nullptr;;
//End of Mouse Sensitivity
	
};
