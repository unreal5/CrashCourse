// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CrashCourse : ModuleRules
{
	public CrashCourse(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange([
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NavigationSystem", "AIModule",
			"GameplayAbilities", "GameplayTags", "GameplayTasks"
		]);
		PrivateDependencyModuleNames.AddRange(["AnimGraphRuntime"]);
		PublicIncludePaths.AddRange(["CrashCourse/", "CrashCourse/Public"]);
	}
}