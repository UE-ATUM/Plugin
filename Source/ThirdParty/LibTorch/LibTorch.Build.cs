// © 2023 Kaya Adrian.

using System.IO;
using UnrealBuildTool;


/**
 * Module which includes the third-party code of LibTorch
 */
public class LibTorch : ModuleRules
{
	// ReSharper disable once InconsistentNaming
	/**
	 * Constructor
	 */
	public LibTorch(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		PCHUsage = PCHUsageMode.NoPCHs;
		IWYUSupport = IWYUSupport.Full;
		CppStandard = CppStandardVersion.Cpp20;
		
		bUseRTTI = true;
		bUseUnity = false;
		bUsePrecompiled = false;
		bEnableExceptions = true;
		
		if (Target!.Platform != UnrealTargetPlatform.Win64)
		{
			EpicGames.Core.Log.TraceError("Cannot load LibTorch on {0}!", Target.Platform.ToString());
			return;
		}
		
		PublicDefinitions.AddRange(new[]
		{
			"NO_EXPORT",
			"WITH_LIBTORCH"
		});
		
		var platformPath = Path.Combine(ModuleDirectory, Target.Platform.ToString());
		AddIncludeFolders(Path.Combine(platformPath, "include"));
		LinkLibraryFiles(Path.Combine(platformPath, "lib"));
	}
	
	/**
	 * Adds folder paths from which files can be included to avoid typing the full path
	 *
	 * @param includePath Path to folder with header files
	 */
	private void AddIncludeFolders(string includePath)
	{
		PublicIncludePaths.AddRange(new[]
		{
			includePath,
			Path.Combine(includePath!, "torch/csrc/api/include")
		});
	}
	
	/**
	 * Links included libraries as project dependencies
	 *
	 * @param libraryPath Path to folder with library files
	 */
	private void LinkLibraryFiles(string libraryPath)
	{
		var filePaths = Directory.GetFiles(libraryPath!, "*", SearchOption.AllDirectories);
		foreach (var filePath in filePaths)
		{
			var fileName = Path.GetFileName(filePath);
			
			if (fileName.EndsWith(".lib"))
			{
				PublicAdditionalLibraries.Add(filePath);
			}
			else if (fileName.EndsWith(".dll"))
			{
				RuntimeDependencies.Add(filePath);
				PublicDelayLoadDLLs.Add(fileName);
			}
			else
			{
				EpicGames.Core.Log.TraceInformation("Ignored file {0}", filePath);
			}
		}
	}
}
