#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/BaseCommonActivatableWidget.h"
#include "MainMenuCAW.generated.h"


UCLASS()
class UE5INTRO_API UMainMenuCAW : public UBaseCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

// Buttons
protected: 
	UFUNCTION()
	void OnStartButtonClicked();
	UFUNCTION()
	void OnQuitButtonClicked();
	UFUNCTION()
	void OnOptionButtonClicked();

protected:
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_Start_Button = nullptr;
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_Quit_Button = nullptr;
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_Option_Button = nullptr;

// End of Buttons
	
};
