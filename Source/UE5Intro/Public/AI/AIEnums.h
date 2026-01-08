#pragma once

#include "CoreMinimal.h"
#include "AIEnums.generated.h"

UENUM()
enum class EAISpeedType : uint8
{
	Normal,
	Attack,
	Defense,
	MAX UMETA(Hidden),
};

UENUM()
enum class EDummyType : uint8
{
	NONE UMETA(Hidden),
	Example1,
	Example2,
	Example3,
	Example4,
	Example5,
	Example6,
	Example7,
	Example8,
	Example9,
	Example10,
	Example11,
	Example12,
	Example13,
	Example14,
	MAX UMETA(Hidden),
};