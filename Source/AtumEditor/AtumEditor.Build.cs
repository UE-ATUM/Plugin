// © 2023 Kaya Adrian.

using UnrealBuildTool;


public class AtumEditor : ModuleRules
{
	public AtumEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.CPlusPlus;
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
