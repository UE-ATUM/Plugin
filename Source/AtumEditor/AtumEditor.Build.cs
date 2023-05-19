// © 2023 Kaya Adrian.

using UnrealBuildTool;


public class AtumEditor : ModuleRules
{
	public AtumEditor(ReadOnlyTargetRules target) : base(target)
	{
		Type = ModuleType.CPlusPlus;
		PCHUsage = PCHUsageMode.NoPCHs;
		CppStandard = CppStandardVersion.Cpp20;
		
		bUseRTTI = true;
		bUseUnity = false;
		bEnforceIWYU = true;
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
