#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUpComponent.generated.h"


UCLASS(ClassGroup = ( "Pick Up" ), meta = ( BlueprintSpawnableComponent ))
class UE5INTRO_API UPickUpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPickUpComponent();	
};
