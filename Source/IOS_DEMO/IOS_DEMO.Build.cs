// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class IOS_DEMO : ModuleRules
{
	public IOS_DEMO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D" });
		PrivateDependencyModuleNames.AddRange(new string[] { "HelpshiftSDK" });

	}
}
