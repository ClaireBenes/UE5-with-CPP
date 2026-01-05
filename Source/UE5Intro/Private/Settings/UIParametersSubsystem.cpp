// UI
#include "Settings/UIParametersSubsystem.h"
#include "UI/MenuNavigationDataAsset.h"
#include "Settings/UIParameters.h"

UMenuNavigationDataAsset* UUIParametersSubsystem::GetMenuNavigationInfo()
{
	// If reference wasn't load, load it now
	if( !MenuNavigationInfo )
	{
		UUIParameters* UIParameters = Cast<UUIParameters>(UUIParameters::StaticClass()->GetDefaultObject());

		if( UIParameters )
		{
			MenuNavigationInfo = Cast<UMenuNavigationDataAsset>(UIParameters->MenuNavigationInfoPath.TryLoad());
		}
	}

	return MenuNavigationInfo;
}
