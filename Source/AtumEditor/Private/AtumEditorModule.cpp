// © 2023 Kaya Adrian.

#include "AtumEditorModule.h"


#define LOCTEXT_NAMESPACE "AtumEditorModule"

void FAtumEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FAssetToolsModule::GetModule().Get();
	AtumAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(
		TEXT("ATUM"),
		LOCTEXT("AtumAssetCategory", "Machine Learning")
	);
	AssetTools.RegisterAssetTypeActions(AtumNeuralNetworkAssetTypeActions);
}

void FAtumEditorModule::ShutdownModule()
{
	if (FAssetToolsModule::IsModuleLoaded())
	{
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(AtumNeuralNetworkAssetTypeActions);
	}
}
	
IMPLEMENT_MODULE(FAtumEditorModule, AtumEditor)

#undef LOCTEXT_NAMESPACE
