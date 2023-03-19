// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using System.Linq;
using UnrealBuildTool;


public class LibTorch : ModuleRules
{
	private readonly string[] _delayLoadDllExceptions = {
		"c10.dll"
	};
	
	public LibTorch(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		CppStandard = CppStandardVersion.Latest;
		bUseRTTI = true;
		bEnableExceptions = true;

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

		if (Target.Configuration == UnrealTargetConfiguration.Shipping)
		{
			PublicDefinitions.AddRange(new []
			{
				"LIBTORCH_DEBUG=0",
				"LIBTORCH_RELEASE=1"
			});

			PlatformPath = Path.Combine(PlatformPath, "Release");
		}
		else
		{
			PublicDefinitions.AddRange(new []
			{
				"LIBTORCH_DEBUG=1",
				"LIBTORCH_RELEASE=0"
			});
			
			PlatformPath = Path.Combine(PlatformPath, "Debug");
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
		var PluginBinariesPath = Path.Combine(PluginDirectory, "Binaries", Target.Platform.ToString());

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
				
				if (_delayLoadDllExceptions.Contains(FileName))
				{
					CopyExceptionFile(FilePath, Path.Combine(PluginBinariesPath, FileName));
				}
				else
				{
					PublicDelayLoadDLLs.Add(FileName);
				}
			}
			else
			{
				EpicGames.Core.Log.TraceInformation("Ignored file {0}", FilePath);
			}
		}
	}

	private static void CopyExceptionFile(string SourcePath, string TargetPath)
	{
		var FileName = Path.GetFileName(SourcePath);
		EpicGames.Core.Log.TraceInformation("Linking LibTorch without /DELAYLOAD:{0}", FileName);
		
		try
		{
			File.Copy(SourcePath, TargetPath, true);
		}
		catch (IOException CopyException)
		{
			EpicGames.Core.Log.TraceInformation(CopyException.Message);
		}
		catch (System.UnauthorizedAccessException AccessException)
		{
			if (File.Exists(TargetPath))
			{
				EpicGames.Core.Log.TraceWarning(AccessException.Message);
			}
			else
			{
				EpicGames.Core.Log.TraceError(
					"Attempted to copy {0} to {1}, but the operation was unauthorized.",
					FileName,
					TargetPath
				);
			}
		}
	}
}
