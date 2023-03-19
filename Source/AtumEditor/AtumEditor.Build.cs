// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class AtumEditor : ModuleRules
{
	public AtumEditor(ReadOnlyTargetRules Target) : base(Target)
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
			"Engine"
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
