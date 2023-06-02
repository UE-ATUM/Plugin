// © 2023 Kaya Adrian.

#include "IAtumModule.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#endif


#define LOCTEXT_NAMESPACE "IAtumModule"

#if PLATFORM_WINDOWS
TArray<TUniquePtr<uint8, FDllDeleter>> IAtumModule::DllHandles;
#endif
const FName IAtumModule::ModuleName = TEXT("Atum");


#if PLATFORM_WINDOWS
void FDllDeleter::operator()(uint8* const DllHandle) const noexcept
{
	if (DllHandle)
	{
		FPlatformProcess::FreeDllHandle(DllHandle);
	}
}
#endif

bool IAtumModule::GetLibraryPath(FString& OutPath) noexcept
{
	const IPlugin* const AtumPlugin = IPluginManager::Get().FindPlugin(ModuleName.ToString()).Get();
	if (AtumPlugin == nullptr)
		return false;
	
	OutPath = AtumPlugin->GetBaseDir() / TEXT("Source/ThirdParty/LibTorch");

#if PLATFORM_WINDOWS
	OutPath /= TEXT("Win64");
#elif
	return false;
#endif

	OutPath /= TEXT("lib");
	return true;
}

#undef LOCTEXT_NAMESPACE
