// © 2023 Kaya Adrian.

#include "IAtumEditor.h"


#define LOCTEXT_NAMESPACE "IAtumEditor"

const FName IAtumEditorModule::ModuleName = TEXT("AtumEditor");

IAtumEditorModule::IAtumEditorModule() noexcept :
AtumAssetCategoryBit(EAssetTypeCategories::None),
AtumNeuralNetworkAssetTypeActions(MakeShared<FAtumNeuralNetworkAssetTypeActions>())
{
}

#undef LOCTEXT_NAMESPACE
