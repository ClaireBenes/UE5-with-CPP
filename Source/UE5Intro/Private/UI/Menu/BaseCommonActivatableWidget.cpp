// UI
#include "UI/Menu/BaseCommonActivatableWidget.h"
#include "UI/Menu/BaseMenuCommonUserWidget.h"
#include "UI/MenuNavigationDataAsset.h"

// Settings
#include "Settings/UIParametersSubsystem.h"
#include "Kismet/GameplayStatics.h"

//Controller
#include "Controller/MainPlayerController.h"

void UBaseCommonActivatableWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Load Data Asset
	UUIParametersSubsystem* UIParametersSubsystem = GEngine->GetEngineSubsystem<UUIParametersSubsystem>();

	if( UIParametersSubsystem )
	{
		MenuNavigationInfoDataAsset = UIParametersSubsystem->GetMenuNavigationInfo();
	}
}

void UBaseCommonActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Get Player Controller
	PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	OpenMenu();
}

void UBaseCommonActivatableWidget::OpenMenu()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UBaseCommonActivatableWidget::CloseMenu()
{
	CloseActivatableWidget();
}

void UBaseCommonActivatableWidget::AddWidgetFromSubsystem(FString InWidgetName)
{
	// Check pointers
	if( !BaseMenuCommonUserWidget.IsValid() || !MenuNavigationInfoDataAsset.IsValid() )
	{
		return;
	}

	// Create the desired widget and push it on the stack
	TSubclassOf<UCommonActivatableWidget> DesiredWidget = *MenuNavigationInfoDataAsset->MenuNavigationActivatableWidgetMap.Find(InWidgetName);
	if( DesiredWidget )
	{
		BaseMenuCommonUserWidget->AddWidgetOnStack(DesiredWidget);
	}
}

void UBaseCommonActivatableWidget::CloseActivatableWidget()
{
	// Turn back on the previous Activatable Widget if valid
	if( PreviousCommonUserWidget.IsValid() )
	{
		PreviousCommonUserWidget->ActivateWidget();
	}

	// Deactivate and hide this one
	DeactivateWidget();
	SetVisibility(ESlateVisibility::Collapsed);
	if( BaseMenuCommonUserWidget.IsValid() )
	{
		BaseMenuCommonUserWidget->RemoveWidgetOnStack(*this);
	}
}

void UBaseCommonActivatableWidget::SetBaseMenuCommonUserWidget(UBaseMenuCommonUserWidget* InBaseMenuCommonUserWidget)
{
	BaseMenuCommonUserWidget = InBaseMenuCommonUserWidget;
}

void UBaseCommonActivatableWidget::SetPreviousCommonUserWidget(UCommonActivatableWidget* InPreviousCommonUserWidget)
{
	PreviousCommonUserWidget = InPreviousCommonUserWidget;
}
