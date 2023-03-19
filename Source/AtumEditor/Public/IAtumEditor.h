// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AssetTypeCategories.h"
#include "AtumNeuralNetworkActions.h"


DECLARE_LOG_CATEGORY_EXTERN(LogAtumEditor, Log, All)

class ATUMEDITOR_API IAtumEditorModule : public IModuleInterface
{
protected:
	EAssetTypeCategories::Type AtumAssetCategoryBit = EAssetTypeCategories::None;
	TSharedRef<FAtumNeuralNetworkAssetTypeActions> AtumNeuralNetworkAssetTypeActions =
		MakeShared<FAtumNeuralNetworkAssetTypeActions>();
	
public:
	static inline const FName ModuleName = TEXT("AtumEditor");

	UE_NODISCARD
	static FORCEINLINE bool IsModuleLoaded() noexcept { return FModuleManager::Get().IsModuleLoaded(ModuleName); }

	UE_NODISCARD
	static FORCEINLINE IAtumEditorModule& GetModule()
	{ return FModuleManager::LoadModuleChecked<IAtumEditorModule>(ModuleName); }

	UE_NODISCARD
	FORCEINLINE EAssetTypeCategories::Type GetAtumAssetCategoryBit() const noexcept { return AtumAssetCategoryBit; }

	UE_NODISCARD
	FORCEINLINE TSharedRef<const FAtumNeuralNetworkAssetTypeActions>
	GetAtumNeuralNetworkAssetTypeActions() const noexcept { return AtumNeuralNetworkAssetTypeActions; }
};
