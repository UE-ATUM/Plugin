// © 2023 Kaya Adrian.

using System.IO;
using UnrealBuildTool;


// ReSharper disable once InconsistentNaming
public class LibTorch : ModuleRules
{
	public LibTorch(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		PCHUsage = PCHUsageMode.NoPCHs;
		CppStandard = CppStandardVersion.Cpp20;
		
		bUseRTTI = true;
		bUseUnity = false;
		bEnforceIWYU = true;
		bUsePrecompiled = false;
		bEnableExceptions = true;

		if (Target.Platform != UnrealTargetPlatform.Win64)
		{
			EpicGames.Core.Log.TraceError("Cannot load LibTorch on {0}!", Target.Platform.ToString());
			return;
		}
		
		PublicDefinitions.AddRange(new []
		{
			"NO_EXPORT",
			"WITH_LIBTORCH"
		});
		
		var PlatformPath = Path.Combine(ModuleDirectory, Target.Platform.ToString());
		AddIncludeFolders(Path.Combine(PlatformPath, "include"));
		LinkLibraryFiles(Path.Combine(PlatformPath, "lib"));
	}

	private void AddIncludeFolders(string IncludePath)
	{
		PublicIncludePaths.AddRange(new []
		{
			IncludePath,
			Path.Combine(IncludePath, "torch/csrc/api/include")
		});
	}

	private void LinkLibraryFiles(string LibraryPath)
	{
		var FilePaths = Directory.GetFiles(LibraryPath, "*", SearchOption.AllDirectories);
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
