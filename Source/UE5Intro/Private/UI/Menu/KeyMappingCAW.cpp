// UI
#include "UI/Menu/KeyMappingCAW.h"
#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"

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
