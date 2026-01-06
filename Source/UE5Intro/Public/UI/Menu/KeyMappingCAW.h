#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "EnhancedActionKeyMapping.h"

#include "KeyMappingCAW.generated.h"

UCLASS(Abstract)
class UE5INTRO_API UKeyMappingCAW : public UCommonActivatableWidget
{
	GENERATED_BODY()

// Keybindings
public:
	void SetInputName(FName InName);
	void SetInputDisplayName(FText InDisplayName);
	void SetInputSelector(FEnhancedActionKeyMapping& GivenKey);

protected:
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UTextBlock> BIND_InputDisplayName_Text = nullptr;
	FName InputName;

	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UInputKeySelector> BIND_InputSelector = nullptr;
	FEnhancedActionKeyMapping DisplayKey;
// End of Keybindings
	
};
