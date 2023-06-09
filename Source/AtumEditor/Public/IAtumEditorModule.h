// © 2023 Kaya Adrian.

#pragma once

#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"

class FAssetTypeActions_AtumNeuralNetwork;


#define LOCTEXT_NAMESPACE "IAtumEditorModule"

class ATUMEDITOR_API IAtumEditorModule : public IModuleInterface
{
protected:
	EAssetTypeCategories::Type AtumAssetCategoryBit;
	TSharedRef<FAssetTypeActions_AtumNeuralNetwork> AtumNeuralNetworkAssetTypeActions;
	
public:
	static const FName ModuleName;
	
	UE_NODISCARD_CTOR
	IAtumEditorModule() noexcept;
	
	UE_NODISCARD
	static FORCEINLINE bool IsModuleLoaded() noexcept { return FModuleManager::Get().IsModuleLoaded(ModuleName); }
	
	UE_NODISCARD
	static FORCEINLINE IAtumEditorModule& GetModule()
	{ return FModuleManager::LoadModuleChecked<IAtumEditorModule>(ModuleName); }
	
	UE_NODISCARD
	FORCEINLINE EAssetTypeCategories::Type GetAtumAssetCategoryBit() const noexcept { return AtumAssetCategoryBit; }
	
	UE_NODISCARD
	FORCEINLINE TSharedRef<const FAssetTypeActions_AtumNeuralNetwork>
	GetAtumNeuralNetworkAssetTypeActions() const noexcept { return AtumNeuralNetworkAssetTypeActions; }
};

#undef LOCTEXT_NAMESPACE
