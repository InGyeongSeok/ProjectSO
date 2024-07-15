// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectSO : ModuleRules
{
	public ProjectSO(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "ALSV4_CPP" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
