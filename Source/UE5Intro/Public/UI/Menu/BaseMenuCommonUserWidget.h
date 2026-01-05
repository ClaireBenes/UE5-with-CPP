#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "BaseMenuCommonUserWidget.generated.h"


UCLASS(Abstract)
class UE5INTRO_API UBaseMenuCommonUserWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Base Menu Common User Widget")
	void AddWidgetOnStack(TSubclassOf<class UCommonActivatableWidget> InWidget);
	void RemoveWidgetOnStack(class UBaseCommonActivatableWidget& InWidget);

protected:
	void CloseBaseMenu();
	
protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonActivatableWidgetStack> BIND_PauseMenuWidgetStack = nullptr;
};
