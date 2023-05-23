// © 2023 Kaya Adrian.

#include "IAtum.h"

#include "Interfaces/IPluginManager.h"


#define LOCTEXT_NAMESPACE "IAtum"

std::vector<void*> IAtumModule::DllHandles;
const FName IAtumModule::ModuleName = TEXT("Atum");

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
