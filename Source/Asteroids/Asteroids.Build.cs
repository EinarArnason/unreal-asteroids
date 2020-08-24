// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Asteroids : ModuleRules
{
	public Asteroids(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
