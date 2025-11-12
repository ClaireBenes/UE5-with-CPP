// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5Intro : ModuleRules
{
	public UE5Intro(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] { "UE5Intro" });
	}
}
