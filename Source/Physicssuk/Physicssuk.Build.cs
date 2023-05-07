// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Physicssuk : ModuleRules
{
	public Physicssuk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { "Physicssuk" });

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "CommonUI", "GameplayTags","DeveloperSettings", "EnhancedInput"});
		PrivateDependencyModuleNames.AddRange(new string[]{"Niagara", "GameSettings", "CommonUI", "CommonInput", "CommonGame", "Advertising", "CommonUser" });
	}
}
