#include "AI/Test/EnvQueryTest_AITeam.h"
#include "AI/AITargetPoint.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

UEnvQueryTest_AITeam::UEnvQueryTest_AITeam(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Indicate cost of the test
	Cost = EEnvTestCost::Low;

	// For test Optimisation, indicate if we work with floats
	SetWorkOnFloatValues(false);

	// Indicate which type of item is expected (either Actor or Vector)
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
}

void UEnvQueryTest_AITeam::RunTest(FEnvQueryInstance& QueryInstance) const
{
	// Check if we have a Querier
	UObject* QueryOwner = QueryInstance.Owner.Get();
	if( !QueryOwner )
	{
		return;
	}

	// Prepare cache to save user's test
	BoolValue.BindData(QueryOwner, QueryInstance.QueryID);
	bool bWantsValid = BoolValue.GetValue(); // Check what we expect from this result

	// Go through each item in the Test
	for( FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It )
	{
		// Check if Item is a Target Point
		const AAITargetPoint* TargetPoint = Cast<AAITargetPoint>(GetItemActor(QueryInstance, It.GetIndex()));
		{
			// Check if Target Point and if Same Team
			if( TargetPoint && ( TargetPoint->GetTeam() == Team ) )
			{
				// Correct Item, pass and set score
				It.SetScore(TestPurpose, FilterType, true, bWantsValid);
			}
			else
			{
				// Not Correct Item, indicate Failed
				It.ForceItemState(EEnvItemStatus::Failed);
			}
		}
	}
}

FText UEnvQueryTest_AITeam::GetDescriptionTitle() const
{
	FString TeamString;
	switch( Team )
	{
		case ETeamType::Blue:
			TeamString = "Blue Team";
			break;
		case ETeamType::Red:
			TeamString = "Red Team";
			break;
		default:
			TeamString = "No Team Selected";
			break;
	}

	return FText::FromString(FString::Printf(TEXT("%s: %s"),
		*Super::GetDescriptionTitle().ToString(), *TeamString));
}

FText UEnvQueryTest_AITeam::GetDescriptionDetails() const
{
	return DescribeBoolTestParams("behavior");
}
