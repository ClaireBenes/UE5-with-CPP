// UI
#include "UI/MainCommonButtonBase.h"
#include "CommonTextBlock.h"

void UMainCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	if( BIND_ButtonCommonText )
	{
		BIND_ButtonCommonText->SetText(ButtonText);
	}
}

void UMainCommonButtonBase::NativeOnClicked()
{
	Super::NativeOnClicked();

	OnButtonClicked.Broadcast();
}
