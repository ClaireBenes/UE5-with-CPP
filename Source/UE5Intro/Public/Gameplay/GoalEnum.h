// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoalEnum.generated.h"

UENUM()
enum class ETeamType : uint8
{
	None UMETA(Hidden),
	Blue,
	Red,
	MAX UMETA(Hidden),
};
