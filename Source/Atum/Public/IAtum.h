// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


DECLARE_LOG_CATEGORY_EXTERN(LogAtum, Log, All)

class ATUM_API IAtumModule : public IModuleInterface
{
protected:
	TArray<void*> DllHandles = TArray<void*>();
	
public:
	static inline const FName ModuleName = TEXT("Atum");

	UE_NODISCARD
	static FORCEINLINE bool IsModuleLoaded() noexcept { return FModuleManager::Get().IsModuleLoaded(ModuleName); }

	UE_NODISCARD
	static FORCEINLINE IAtumModule& GetModule() { return FModuleManager::LoadModuleChecked<IAtumModule>(ModuleName); }
	
	FORCEINLINE void GetDllHandles(TArray<const void*>& OutValue) const noexcept { OutValue.Append(DllHandles); }
};
