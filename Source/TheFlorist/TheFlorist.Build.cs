// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheFlorist : ModuleRules
{
	public TheFlorist(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
										"HeadMountedDisplay", "GameplayTasks", "GameplayTags", "Niagara",
										"NavigationSystem" });
	}
}
