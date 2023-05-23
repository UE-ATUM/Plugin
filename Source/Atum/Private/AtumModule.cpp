// © 2023 Kaya Adrian.

#include "AtumModule.h"

#include "AtumMacros.h"
#include "AtumSettings.h"
#include "HAL/FileManager.h"
#include "Kismet/GameplayStatics.h"

LIBTORCH_INCLUDES_START
#include <torch/custom_class.h>
#include <torch/version.h>
LIBTORCH_INCLUDES_END


#define LOCTEXT_NAMESPACE "AtumModule"

void FAtumModule::StartupModule()
{
#ifndef WITH_LIBTORCH
	ATUM_LOG(Fatal, TEXT("Could not start ATUM module because LibTorch is missing!"))
#endif
	
	FString LibraryPath;
	if (!GetLibraryPath(LibraryPath))
	{
		ATUM_LOG(Fatal, TEXT("Cannot load LibTorch on platform: %s"), *UGameplayStatics::GetPlatformName())
		return;
	}
	
	const TCHAR* const LibraryPathPointer = *LibraryPath;
	ATUM_LOG(Warning, TEXT("Loading LibTorch libraries from path: %s"), LibraryPathPointer)

#if PLATFORM_WINDOWS
	FPlatformProcess::AddDllDirectory(LibraryPathPointer);
	
	TArray<FString> DllNames;
	IFileManager::Get().FindFilesRecursive(
		DllNames,
		LibraryPathPointer,
		TEXT("*.dll"),
		true,
		false,
		false
	);
	
	DllHandles.Reserve(DllNames.Num());
	for (const FString& DllName : DllNames)
	{
		DllHandles.Emplace(static_cast<uint8*>(FPlatformProcess::GetDllHandle(*DllName)));
	}
#endif
	
	torch::init();
	UE_LOG(LogAtum, Warning, TEXT("Loaded LibTorch %s!"), TEXT(TORCH_VERSION));
}

void FAtumModule::ShutdownModule()
{
	UE_LOG(LogAtum, Warning, TEXT("Unloaded LibTorch %s!"), TEXT(TORCH_VERSION))
}

IMPLEMENT_MODULE(FAtumModule, Atum)

#undef LOCTEXT_NAMESPACE
