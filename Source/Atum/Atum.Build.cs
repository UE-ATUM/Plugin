// © 2023 Kaya Adrian.

using UnrealBuildTool;


// ReSharper disable once InconsistentNaming
public class Atum : ModuleRules
{
	public Atum(ReadOnlyTargetRules Target) : base(Target)
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
