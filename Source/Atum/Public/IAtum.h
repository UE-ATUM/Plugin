// © 2023 Kaya Adrian.

#pragma once

#include "Modules/ModuleManager.h"

#include <vector>


#define LOCTEXT_NAMESPACE "IAtum"

class ATUM_API IAtumModule : public IModuleInterface
{
protected:
	static inline std::vector<void*> DllHandles;
	
public:
	static inline const FName ModuleName = TEXT("Atum");

	static bool GetLibraryPath(FString& OutPath) noexcept;

	UE_NODISCARD
	static FORCEINLINE bool IsModuleLoaded() noexcept { return FModuleManager::Get().IsModuleLoaded(ModuleName); }

	UE_NODISCARD
	static FORCEINLINE IAtumModule& GetModule() { return FModuleManager::LoadModuleChecked<IAtumModule>(ModuleName); }

	UE_NODISCARD
	static FORCEINLINE const std::vector<void*>& GetDllHandles() noexcept { return DllHandles; }
};

#undef LOCTEXT_NAMESPACE
