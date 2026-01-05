#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UIParameters.generated.h"


UCLASS(Config = Engine, BlueprintType, Blueprintable, defaultconfig, meta = (DisplayName = "UI Parameters"))
class UE5INTRO_API UUIParameters : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(config, EditAnywhere, Category = Settings, meta = (AllowedClasses = "/Script/Engine.DataAsset" ))
	FSoftObjectPath MenuNavigationInfoPath;
};
