#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "MainCommonButtonBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

UCLASS()
class UE5INTRO_API UMainCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

// Text
protected:
	UPROPERTY(EditAnywhere, Category = "Main Button")
	FText ButtonText = FText();
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonTextBlock> BIND_ButtonCommonText = nullptr;
// End of Text


// Event
protected:
	// Override this function to call our On Click Event
	virtual void NativeOnClicked() override;

public:
	FOnButtonClicked OnButtonClicked;
// End of Event
};
