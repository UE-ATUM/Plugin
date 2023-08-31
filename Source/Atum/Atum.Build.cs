// © 2023 Kaya Adrian.

using UnrealBuildTool;


/**
 * Module which implements runtime functionality of ATUM
 */
public class Atum : ModuleRules
{
	// ReSharper disable once InconsistentNaming
	/**
	 * Constructor
	 */
	public Atum(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.CPlusPlus;
		PCHUsage = PCHUsageMode.NoPCHs;
		IWYUSupport = IWYUSupport.Full;
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
