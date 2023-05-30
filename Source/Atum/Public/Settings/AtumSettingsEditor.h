// © 2023 Kaya Adrian.

#pragma once

#include "Settings/AtumSettingsBase.h"

#include "AtumSettingsEditor.generated.h"


#define LOCTEXT_NAMESPACE "AtumSettingsEditor"

/**
 * @brief ATUM settings that control editor features
 */
UCLASS(MinimalAPI, BlueprintType, DisplayName = "ATUM Editor Settings")
class UAtumSettingsEditor : public UAtumSettingsBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, DisplayName = "Enable LogAtumEditor", meta = (
		AllowPrivateAccess,
		ConsoleVariable = "atum.Editor.EnableLogAtumEditor"
	))
	bool bLogAtumEditorEnabled;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, DisplayName = "Allow Blueprintable Classes", meta = (
		AllowPrivateAccess,
		ConsoleVariable = "atum.Editor.AllowBlueprintableClasses"
	))
	bool bBlueprintableClassesAllowed;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta = (
		AllowPrivateAccess,
		ConfigRestartRequired = "true"
	))
	FColor NeuralNetworkAssetTypeColor;
	
public:
	UE_NODISCARD_CTOR
	UAtumSettingsEditor() noexcept;
	
#if WITH_EDITOR
	UE_NODISCARD
	virtual FText GetSectionText() const override;
	
	UE_NODISCARD
	virtual FText GetSectionDescription() const override;
#endif
	
	UE_NODISCARD
	FORCEINLINE bool IsLogAtumEditorEnabled() const noexcept { return bLogAtumEditorEnabled; }
	
	UE_NODISCARD
	FORCEINLINE void SetLogAtumEditorEnabled(const bool bValue) noexcept { bLogAtumEditorEnabled = bValue; }
	
	UE_NODISCARD
	FORCEINLINE bool AreBlueprintableClassesAllowed() const noexcept { return bBlueprintableClassesAllowed; }
	
	UE_NODISCARD
	FORCEINLINE void SetBlueprintableClassesAllowed(const bool bValue) noexcept
	{ bBlueprintableClassesAllowed = bValue; }
	
	UE_NODISCARD
	FORCEINLINE FColor GetNeuralNetworkAssetTypeColor() const noexcept { return NeuralNetworkAssetTypeColor; }
};

#undef LOCTEXT_NAMESPACE
