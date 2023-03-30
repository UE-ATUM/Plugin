// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class AtumEditor : ModuleRules
{
	public AtumEditor(ReadOnlyTargetRules target) : base(target)
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
			"CoreUObject"
		});
		
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"AssetTools",
			"Slate",
			"SlateCore",
			"UnrealEd"
		});
	}
}
