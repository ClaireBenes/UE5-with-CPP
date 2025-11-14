#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GravityDataAsset.generated.h"


UCLASS()
class UE5INTRO_API UGravityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector AngularForce = FVector(0.0f, 0.0f, 0.0f);	
};
