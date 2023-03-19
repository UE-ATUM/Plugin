// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class Atum : ModuleRules
{
	public Atum(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;
		bUseRTTI = true;
		bEnforceIWYU = true;
		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"LibTorch"
		});
		
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"DeveloperSettings",
			"Projects"
		});
	}
}
