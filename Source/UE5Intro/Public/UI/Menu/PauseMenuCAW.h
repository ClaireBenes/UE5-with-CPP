#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/BaseCommonActivatableWidget.h"
#include "PauseMenuCAW.generated.h"


UCLASS(Abstract)
class UE5INTRO_API UPauseMenuCAW : public UBaseCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void OpenMenu() override;
	virtual void CloseMenu() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);


// Button
protected:
	UFUNCTION()
	void OnRestartButtonClicked();
	UFUNCTION()
	void OnQuitButtonClicked();
	UFUNCTION()
	void OnOptionButtonClicked();
	UFUNCTION()
	void OnMainMenuButtonClicked();

protected:
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_Resume_Button = nullptr;
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_Restart_Button = nullptr;
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_Quit_Button = nullptr;
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_MainMenu_Button = nullptr;
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_Option_Button = nullptr;
	UPROPERTY(EditAnywhere, Category = "Pause Menu")
	FName MainMenudMapName = "LVL_MainMenu";
// End of Button
	
};
