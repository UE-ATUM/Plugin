// © 2023 Kaya Adrian.

using System.IO;
using UnrealBuildTool;


public class LibTorch : ModuleRules
{
	public LibTorch(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		PCHUsage = PCHUsageMode.NoPCHs;
		CppStandard = CppStandardVersion.Cpp20;
		
		bUseRTTI = true;
		bUseUnity = false;
		bUsePrecompiled = false;
		bEnableExceptions = true;
		
		PrivateDependencyModuleNames.AddRange(new []
		{
			"Core"
		});

		if (Target.Platform != UnrealTargetPlatform.Win64)
		{
			PublicDefinitions.AddRange(new []
			{
				"HAS_LIBTORCH=0",
				"LIBTORCH_DEBUG=0",
				"LIBTORCH_RELEASE=0"
			});

			EpicGames.Core.Log.TraceError("Cannot load LibTorch on {0}!", Target.Platform.ToString());
			return;
		}
		
		PublicDefinitions.Add("HAS_LIBTORCH=1");
		var PlatformPath = Path.Combine(ModuleDirectory, Target.Platform.ToString());

		if (Target.Configuration == UnrealTargetConfiguration.DebugGame)
		{
			PublicDefinitions.AddRange(new []
			{
				"LIBTORCH_DEBUG=1",
				"LIBTORCH_RELEASE=0"
			});
			
			PlatformPath = Path.Combine(PlatformPath, "Debug");
		}
		else
		{
			PublicDefinitions.AddRange(new []
			{
				"LIBTORCH_DEBUG=0",
				"LIBTORCH_RELEASE=1"
			});

			PlatformPath = Path.Combine(PlatformPath, "Release");
		}

		AddIncludeFolders(Path.Combine(PlatformPath, "include"));
		LinkLibraryFiles(Path.Combine(PlatformPath, "lib"));
	}

	private void AddIncludeFolders(string IncludePath)
	{
		PublicIncludePaths.Add(IncludePath);
		
		var FolderPaths = Directory.GetDirectories(IncludePath, "include", SearchOption.AllDirectories);
		foreach (var FolderPath in FolderPaths)
		{
			PublicIncludePaths.Add(FolderPath);
		}
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
