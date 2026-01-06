#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/BaseCommonActivatableWidget.h"
#include "KeyMappingsMenuCAW.generated.h"


UCLASS(Abstract)
class UE5INTRO_API UKeyMappingsMenuCAW : public UBaseCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

// Button
protected:
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UMainCommonButtonBase> BIND_ExitMenu_Button = nullptr;
// End of Button

// Key Mappings
protected:
	void DisplayKeys();

protected:
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UVerticalBox> BIND_KeyMappingMovement_VB = nullptr;
	UPROPERTY(meta = ( BindWidgetOptional ))
	TObjectPtr<class UVerticalBox> BIND_KeyMappingAction_VB = nullptr;

	UPROPERTY(EditAnywhere, Category = "Option User Widget")
	FString KeyMappingWidgetName = FString();

	UPROPERTY(EditAnywhere, Category = "Key Mapping User Widget")
	FString MovementCategoryName = "Movement";
	UPROPERTY(EditAnywhere, Category = "Key Mapping User Widget")
	FString ActionCategoryName = "Action";
// End of Key Mappings
	
};
