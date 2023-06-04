// © 2023 Kaya Adrian.

#pragma once

#include "AssetTypeActions_Base.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions_AtumNeuralNetwork"

class ATUMEDITOR_API FAssetTypeActions_AtumNeuralNetwork : public FAssetTypeActions_Base
{
public:
	UE_NODISCARD
	virtual UClass* GetSupportedClass() const override;
	
	UE_NODISCARD
	virtual FText GetName() const override;
	
	UE_NODISCARD
	virtual FColor GetTypeColor() const override;
	
	UE_NODISCARD
	virtual uint32 GetCategories() override;
	
	virtual void OpenAssetEditor(
		const TArray<UObject*>& InObjects,
		TSharedPtr<IToolkitHost> EditWithinLevelEditor
	) override;
};

#undef LOCTEXT_NAMESPACE
