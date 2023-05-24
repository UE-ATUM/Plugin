// © 2023 Kaya Adrian.

#pragma once

#include "Toolkits/AssetEditorToolkit.h"

class UAtumNeuralNetwork;


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkEditorToolkit"

class ATUMEDITOR_API FAtumNeuralNetworkEditorToolkit : public FAssetEditorToolkit, public FGCObject
{
	UAtumNeuralNetwork* NeuralNetwork;
	
public:
	static const FName AtumNeuralNetworkAppIdentifier;
	
	UE_NODISCARD_CTOR
	FAtumNeuralNetworkEditorToolkit() noexcept;
	
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
	virtual FText GetToolkitName() const override;
	
	UE_NODISCARD
	virtual FString GetWorldCentricTabPrefix() const override;
	
	UE_NODISCARD
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	
	UE_NODISCARD
	virtual FString GetReferencerName() const override;
};

#undef LOCTEXT_NAMESPACE
