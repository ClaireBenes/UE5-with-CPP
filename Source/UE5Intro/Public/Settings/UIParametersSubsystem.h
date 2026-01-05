#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "UIParametersSubsystem.generated.h"


UCLASS()
class UE5INTRO_API UUIParametersSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	class UMenuNavigationDataAsset* GetMenuNavigationInfo();

protected:
	UPROPERTY(transient)
	TObjectPtr< class UMenuNavigationDataAsset> MenuNavigationInfo;
};
