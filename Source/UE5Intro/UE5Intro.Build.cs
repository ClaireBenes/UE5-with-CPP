// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5Intro : ModuleRules
{
	public UE5Intro(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", 
			"InputCore", "EnhancedInput", "UMG", "SlateCore", "Slate" });

		PrivateDependencyModuleNames.AddRange(new string[] { "SlateCore", "Slate" });

		PublicIncludePaths.AddRange(new string[] { "UE5Intro" });
	}
}
