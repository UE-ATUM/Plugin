// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class Atum : ModuleRules
{
	public Atum(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.NoPCHs;
		CppStandard = CppStandardVersion.Cpp20;
		
		bUseRTTI = true;
		bUseUnity = false;
		bUsePrecompiled = false;
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
