// UI
#include "UI/Menu/BaseMenuCommonUserWidget.h"
#include "UI/Menu/BaseCommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CommonActivatableWidget.h"

void UBaseMenuCommonUserWidget::AddWidgetOnStack(TSubclassOf<class UCommonActivatableWidget> InWidget)
{
	// Check Pointer
	if( !BIND_PauseMenuWidgetStack || !InWidget )
	{
		return;
	}

	// Get current displayed widget
	UCommonActivatableWidget* PreviousWidget = BIND_PauseMenuWidgetStack->GetActiveWidget();

	// Create or get new widget to display
	UCommonActivatableWidget* NewWidget = BIND_PauseMenuWidgetStack->AddWidget(InWidget);

	// Update pointer for our  Activatable widget
	UBaseCommonActivatableWidget* BaseWidget = Cast<UBaseCommonActivatableWidget>(NewWidget);
	if( BaseWidget )
	{
		BaseWidget->SetBaseMenuCommonUserWidget(this);
		BaseWidget->SetPreviousCommonUserWidget(PreviousWidget);
	}
}

void UBaseMenuCommonUserWidget::RemoveWidgetOnStack(UBaseCommonActivatableWidget& InWidget)
{
	// Check stack
	if( !BIND_PauseMenuWidgetStack )
	{
		return;
	}

	// Remove widget from stack
	BIND_PauseMenuWidgetStack->RemoveWidget(InWidget);

	// when we call RemoveWidget, we don't necesseraly remove the item from the WidgetList
	// We just Deactivate it
	// We need to use a for loop to make sure that all the items are closed

	// If there's no widget, we can close it
	if( BIND_PauseMenuWidgetStack->GetNumWidgets() == 0 )
	{
		CloseBaseMenu();
	}
	else
	{
		bool bIsDeactivated = true;
		const TArray<UCommonActivatableWidget*>& WidgetList = BIND_PauseMenuWidgetStack->GetWidgetList();

		for( UCommonActivatableWidget* Widget : WidgetList )
		{
			if( Widget->IsActivated() )
			{
				bIsDeactivated = false;
				break;
			}
		}

		if( bIsDeactivated )
		{
			CloseBaseMenu();
		}
	}
}

void UBaseMenuCommonUserWidget::CloseBaseMenu()
{
	SetVisibility(ESlateVisibility::Collapsed);
	RemoveFromParent();
}
