// © 2023 Kaya Adrian.

#include "Atum.h"

#include "HAL/FileManager.h"
#include "Kismet/GameplayStatics.h"
#include "LibTorch/Include.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#endif


#define LOCTEXT_NAMESPACE "FAtumModule"

void FAtumModule::StartupModule()
{
#if HAS_LIBTORCH
	FString LibraryPath;
	if (!GetLibraryPath(LibraryPath))
	{
		UE_LOG(LogAtum, Fatal, TEXT("Cannot load LibTorch on platform: %s"), *UGameplayStatics::GetPlatformName())
		return;
	}

	const TCHAR* const LibraryPathPointer = *LibraryPath;
	UE_LOG(LogAtum, Display, TEXT("Loading LibTorch libraries from path: %s"), LibraryPathPointer)

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
		
	DllHandles.reserve(DllNames.Num());
	for (const FString& DllName : DllNames)
	{
		DllHandles.push_back(FPlatformProcess::GetDllHandle(*DllName));
	}
#endif

	torch::init();
	UE_LOG(LogAtum, Warning, TEXT("Loaded LibTorch %s!"), TEXT(TORCH_VERSION));
#endif
}

void FAtumModule::ShutdownModule()
{
#if PLATFORM_WINDOWS
	for (void* const DllHandle : DllHandles)
	{
		if (DllHandle)
		{
			FPlatformProcess::FreeDllHandle(DllHandle);
		}
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAtumModule, Atum)
