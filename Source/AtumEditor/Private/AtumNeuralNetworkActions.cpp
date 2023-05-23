// © 2023 Kaya Adrian.

#include "AtumNeuralNetworkActions.h"

#include "AtumEditorModule.h"
#include "AtumNeuralNetworkEditorToolkit.h"
#include "AtumSettings.h"
#include "Layers/AtumNeuralNetwork.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkActions"

UClass* FAtumNeuralNetworkAssetTypeActions::GetSupportedClass() const
{
	return UAtumNeuralNetwork::StaticClass();
}

FText FAtumNeuralNetworkAssetTypeActions::GetName() const
{
	return LOCTEXT("AssetTypeActionsName", "ATUM Neural Network");
}

FColor FAtumNeuralNetworkAssetTypeActions::GetTypeColor() const
{
	return GetDefault<UAtumSettings>()->GetNeuralNetworkAssetTypeColor();
}

uint32 FAtumNeuralNetworkAssetTypeActions::GetCategories()
{
	return FAtumEditorModule::GetModule().GetAtumAssetCategoryBit();
}

void FAtumNeuralNetworkAssetTypeActions::OpenAssetEditor(
	const TArray<UObject*>& InObjects,
	const TSharedPtr<IToolkitHost> EditWithinLevelEditor
)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ?
		EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (TArray<UObject*>::TConstIterator Iterator = InObjects.CreateConstIterator(); Iterator; ++Iterator)
	{
		if (auto* const AtumNeuralNetwork = Cast<UAtumNeuralNetwork>(*Iterator); AtumNeuralNetwork)
		{
			MakeShared<FAtumNeuralNetworkEditorToolkit>()->InitEditor(Mode, EditWithinLevelEditor, AtumNeuralNetwork);
		}
	}
}

#undef LOCTEXT_NAMESPACE
