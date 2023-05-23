// © 2023 Kaya Adrian.

#include "IAtumEditorModule.h"


#define LOCTEXT_NAMESPACE "IAtumEditorModule"

const FName IAtumEditorModule::ModuleName = TEXT("AtumEditor");

IAtumEditorModule::IAtumEditorModule() noexcept :
AtumAssetCategoryBit(EAssetTypeCategories::None),
AtumNeuralNetworkAssetTypeActions(MakeShared<FAtumNeuralNetworkAssetTypeActions>())
{
}

#undef LOCTEXT_NAMESPACE
