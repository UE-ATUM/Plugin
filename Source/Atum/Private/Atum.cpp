// Copyright Epic Games, Inc. All Rights Reserved.

#include "Atum.h"

#include "Interfaces/IPluginManager.h"
#include "LibTorch.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#endif

namespace
{
	bool GetLibraryPath(FString& OutPath)
	{
		const IPlugin* const AtumPlugin = IPluginManager::Get().FindPlugin(TEXT("Atum")).Get();
		if (AtumPlugin == nullptr)
			return false;

		OutPath = AtumPlugin->GetBaseDir() / TEXT("Source/ThirdParty/LibTorch");

#if PLATFORM_WINDOWS
		OutPath /= TEXT("Win64");
#endif

#if LIBTORCH_DEBUG
		OutPath /= TEXT("Debug");
#elif LIBTORCH_RELEASE
		OutPath /= TEXT("Release");
#endif

		OutPath /= TEXT("lib");
		return true;
	}
}

#define LOCTEXT_NAMESPACE "FAtumModule"

void FAtumModule::StartupModule()
{
#if HAS_LIBTORCH
#if PLATFORM_WINDOWS
	if (FString LibraryPath; GetLibraryPath(LibraryPath))
	{
		FPlatformProcess::AddDllDirectory(*LibraryPath);
		
		TArray<FString> DllNames;
		IFileManager::Get().FindFilesRecursive(
			DllNames,
			*LibraryPath,
			TEXT("*.dll"),
			true,
			false,
			false
		);

		DllHandles.Reserve(DllNames.Num());
		for (const FString& DllName : DllNames)
		{
			DllHandles.Add(FPlatformProcess::GetDllHandle(*DllName));
		}
	}
#endif
	
	UE_LOG(LogAtum, Warning, TEXT("Loaded LibTorch %s!"), TEXT(TORCH_VERSION));
#endif
}

void FAtumModule::ShutdownModule()
{
#if PLATFORM_WINDOWS
	for (void* const& DllHandle : DllHandles)
	{
		FPlatformProcess::FreeDllHandle(DllHandle);
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAtumModule, Atum)
