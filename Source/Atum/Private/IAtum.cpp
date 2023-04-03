// © 2023 Kaya Adrian.

#include "IAtum.h"

#include "Interfaces/IPluginManager.h"


DEFINE_LOG_CATEGORY(LogAtum)

bool IAtumModule::GetLibraryPath(FString& OutPath)
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

#if LIBTORCH_DEBUG
	OutPath /= TEXT("Debug");
#elif LIBTORCH_RELEASE
	OutPath /= TEXT("Release");
#endif

	OutPath /= TEXT("lib");
	return true;
}
