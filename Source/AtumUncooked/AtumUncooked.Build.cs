// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class AtumUncooked : ModuleRules
{
	public AtumUncooked(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;
		bUseRTTI = true;
		bEnforceIWYU = true;
		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Atum",
			"Core",
			"CoreUObject",
			"Engine",
			"LibTorch"
		});
		
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"BlueprintGraph",
			"KismetCompiler",
			"UnrealEd"
		});
	}
}
