// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"


DECLARE_LOG_CATEGORY_EXTERN(LogAtumUncooked, Log, All)

class ATUMUNCOOKED_API IAtumUncookedModule : public IModuleInterface
{
public:
	static inline const FName ModuleName = TEXT("AtumUncooked");

	UE_NODISCARD
	static FORCEINLINE bool IsModuleLoaded() noexcept { return FModuleManager::Get().IsModuleLoaded(ModuleName); }

	UE_NODISCARD
	static FORCEINLINE IAtumUncookedModule& GetModule()
	{ return FModuleManager::LoadModuleChecked<IAtumUncookedModule>(ModuleName); }
};
