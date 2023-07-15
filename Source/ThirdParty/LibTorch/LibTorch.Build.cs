// © 2023 Kaya Adrian.

using System.IO;
using UnrealBuildTool;


public class LibTorch : ModuleRules
{
	public LibTorch(ReadOnlyTargetRules target) : base(target)
	{
		Type = ModuleType.External;
		PCHUsage = PCHUsageMode.NoPCHs;
		IWYUSupport = IWYUSupport.Full;
		CppStandard = CppStandardVersion.Cpp20;
		
		bUseRTTI = true;
		bUseUnity = false;
		bUsePrecompiled = false;
		bEnableExceptions = true;

		if (target!.Platform != UnrealTargetPlatform.Win64)
		{
			EpicGames.Core.Log.TraceError("Cannot load LibTorch on {0}!", target.Platform.ToString());
			return;
		}
		
		PublicDefinitions.AddRange(new[]
		{
			"NO_EXPORT",
			"WITH_LIBTORCH"
		});
		
		var PlatformPath = Path.Combine(ModuleDirectory, target.Platform.ToString());
		AddIncludeFolders(Path.Combine(PlatformPath, "include"));
		LinkLibraryFiles(Path.Combine(PlatformPath, "lib"));
	}

	private void AddIncludeFolders(string includePath)
	{
		PublicIncludePaths.AddRange(new[]
		{
			includePath,
			Path.Combine(includePath!, "torch/csrc/api/include")
		});
	}

	private void LinkLibraryFiles(string libraryPath)
	{
		var FilePaths = Directory.GetFiles(libraryPath!, "*", SearchOption.AllDirectories);
		foreach (var FilePath in FilePaths)
		{
			var FileName = Path.GetFileName(FilePath);

			if (FileName.EndsWith(".lib"))
			{
				PublicAdditionalLibraries.Add(FilePath);
			}
			else if (FileName.EndsWith(".dll"))
			{
				RuntimeDependencies.Add(FilePath);
				PublicDelayLoadDLLs.Add(FileName);
			}
			else
			{
				EpicGames.Core.Log.TraceInformation("Ignored file {0}", FilePath);
			}
		}
	}
}
