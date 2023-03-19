// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssetTypeActions_Base.h"


class ATUMEDITOR_API FAtumNeuralNetworkAssetTypeActions : public FAssetTypeActions_Base
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
