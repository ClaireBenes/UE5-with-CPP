#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AI/AIEnums.h"
#include "AISpeedDataAsset.generated.h"


UCLASS()
class UE5INTRO_API UAISpeedDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Speed Assets")
	float SpeedByTypeMap[(uint8) EAISpeedType::MAX];
};
