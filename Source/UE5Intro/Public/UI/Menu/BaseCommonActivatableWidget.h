#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseCommonActivatableWidget.generated.h"


UCLASS(Abstract)
class UE5INTRO_API UBaseCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OpenMenu();
	UFUNCTION()
	virtual void CloseMenu();

	void AddWidgetFromSubsystem(FString InWidgetName);
	void CloseActivatableWidget();

public:
	void SetBaseMenuCommonUserWidget(class UBaseMenuCommonUserWidget* InBaseMenuCommonUserWidget);
	void SetPreviousCommonUserWidget(class UCommonActivatableWidget* InPreviousCommonUserWidget);

protected:
	TWeakObjectPtr<class AMainPlayerController> PlayerController = nullptr;

	// Background Widget that contains the Activatable Widget Stack
	TWeakObjectPtr<class UBaseMenuCommonUserWidget> BaseMenuCommonUserWidget = nullptr;
	// Previous Dispayed Widget on the BaseMenuCommonUserWidget
	TWeakObjectPtr<class UCommonActivatableWidget> PreviousCommonUserWidget = nullptr;
	// Reference to the Data Asset, so we can create new widgets
	TWeakObjectPtr<class UMenuNavigationDataAsset> MenuNavigationInfoDataAsset = nullptr;
};
