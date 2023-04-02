// © 2023 Kaya Adrian.

#pragma once

#include "Toolkits/AssetEditorToolkit.h"

class UAtumNeuralNetwork;


class ATUMEDITOR_API FAtumNeuralNetworkEditorToolkit : public FAssetEditorToolkit
{
	UAtumNeuralNetwork* NeuralNetwork = nullptr;
	
public:
	void InitEditor(
		EToolkitMode::Type Mode,
		const TSharedPtr<IToolkitHost>& InitToolkitHost,
		UAtumNeuralNetwork* ObjectToEdit
	) noexcept;

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	UE_NODISCARD
	virtual FName GetToolkitFName() const override;

	UE_NODISCARD
	virtual FText GetBaseToolkitName() const override;

	UE_NODISCARD
	virtual FString GetWorldCentricTabPrefix() const override;

	UE_NODISCARD
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
};
