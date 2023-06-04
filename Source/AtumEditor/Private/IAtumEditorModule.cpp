// © 2023 Kaya Adrian.

#include "IAtumEditorModule.h"

#include "Assets/Network/AssetTypeActions_AtumNeuralNetwork.h"


#define LOCTEXT_NAMESPACE "IAtumEditorModule"

const FName IAtumEditorModule::ModuleName = TEXT("AtumEditor");


IAtumEditorModule::IAtumEditorModule() noexcept :
AtumAssetCategoryBit(EAssetTypeCategories::None),
AtumNeuralNetworkAssetTypeActions(MakeShared<FAssetTypeActions_AtumNeuralNetwork>())
{
}

#undef LOCTEXT_NAMESPACE
