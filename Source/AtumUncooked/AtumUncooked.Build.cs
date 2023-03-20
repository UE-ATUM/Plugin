// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class AtumUncooked : ModuleRules
{
	public AtumUncooked(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.NoPCHs;
		CppStandard = CppStandardVersion.Cpp20;

		bUseRTTI = true;
		bUseUnity = false;
		bUsePrecompiled = false;
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
