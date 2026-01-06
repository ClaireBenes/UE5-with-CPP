#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MenuNavigationDataAsset.generated.h"


UCLASS()
class UE5INTRO_API UMenuNavigationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Menu Navigation")
	TMap<FString, TSubclassOf<class UUserWidget>> MenuNavigationMap;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Menu Navigation")
	TMap<FString, TSubclassOf<class UCommonActivatableWidget>> MenuNavigationActivatableWidgetMap;
};
