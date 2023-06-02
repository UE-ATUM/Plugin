// © 2023 Kaya Adrian.

#pragma once

#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"


#define LOCTEXT_NAMESPACE "IAtumModule"

#if PLATFORM_WINDOWS
struct FDllDeleter
{
	void operator()(uint8* DllHandle) const noexcept;
};
#endif


class ATUM_API IAtumModule : public IModuleInterface
{
protected:
#if PLATFORM_WINDOWS
	static TArray<TUniquePtr<uint8, FDllDeleter>> DllHandles;
#endif
	
public:
	static const FName ModuleName;
	
	static FORCEINLINE FString GetContentDirectory(const FString& AppendedPath = TEXT("")) noexcept
	{ return IPluginManager::Get().FindPlugin(ModuleName.ToString())->GetContentDir() / AppendedPath; }
	
	static bool GetLibraryPath(FString& OutPath) noexcept;
	
	UE_NODISCARD
	static FORCEINLINE bool IsModuleLoaded() noexcept { return FModuleManager::Get().IsModuleLoaded(ModuleName); }
	
	UE_NODISCARD
	static FORCEINLINE IAtumModule& GetModule() { return FModuleManager::LoadModuleChecked<IAtumModule>(ModuleName); }
	
#if PLATFORM_WINDOWS
	UE_NODISCARD
	static FORCEINLINE const TArray<TUniquePtr<uint8, FDllDeleter>>& GetDllHandles() noexcept { return DllHandles; }
#endif
};

#undef LOCTEXT_NAMESPACE
