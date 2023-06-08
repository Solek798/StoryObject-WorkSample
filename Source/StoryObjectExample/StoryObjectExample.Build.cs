// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StoryObjectExample : ModuleRules
{
	public StoryObjectExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput",
			"UMG",
			"LevelSequence",
			"MovieScene"
		});
	}
}
