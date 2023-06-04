// © 2023 Kaya Adrian.

#include "Assets/Network/AssetTypeActions_AtumNeuralNetwork.h"

#include "Assets/Network/AtumNeuralNetworkEditorToolkit.h"
#include "IAtumEditorModule.h"
#include "Layers/Network/AtumNeuralNetwork.h"
#include "Settings/AtumSettingsEditor.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions_AtumNeuralNetwork"

UClass* FAssetTypeActions_AtumNeuralNetwork::GetSupportedClass() const
{
	return UAtumNeuralNetwork::StaticClass();
}

FText FAssetTypeActions_AtumNeuralNetwork::GetName() const
{
	return LOCTEXT("AssetTypeActionsName", "ATUM Neural Network");
}

FColor FAssetTypeActions_AtumNeuralNetwork::GetTypeColor() const
{
	return GetDefault<UAtumSettingsEditor>()->GetNeuralNetworkAssetTypeColor();
}

uint32 FAssetTypeActions_AtumNeuralNetwork::GetCategories()
{
	return IAtumEditorModule::GetModule().GetAtumAssetCategoryBit();
}

void FAssetTypeActions_AtumNeuralNetwork::OpenAssetEditor(
	const TArray<UObject*>& InObjects,
	const TSharedPtr<IToolkitHost> EditWithinLevelEditor
)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ?
		EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	
	for (TArray<UObject*>::TConstIterator Iterator = InObjects.CreateConstIterator(); Iterator; ++Iterator)
	{
		if (auto* const NeuralNetwork = Cast<UAtumNeuralNetwork>(*Iterator); NeuralNetwork)
		{
			MakeShared<FAtumNeuralNetworkEditorToolkit>()->InitEditor(Mode, EditWithinLevelEditor, NeuralNetwork);
		}
	}
}

#undef LOCTEXT_NAMESPACE
