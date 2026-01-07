#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OptionSaveGame.generated.h"


UCLASS()
class UE5INTRO_API UOptionSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	float GetMouseSensitivityX() const;
	float GetMouseSensitivityY() const;
	void SetMouseSensitivityX(float InSensitivity);
	void SetMouseSensitivityY(float InSensitivity);

protected:
	UPROPERTY(SaveGame)
	float MouseSensitivityX = 1.0f;
	UPROPERTY(SaveGame)
	float MouseSensitivityY = 1.0f;
};
