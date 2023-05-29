// © 2023 Kaya Adrian.

#pragma once

#include "Engine/DeveloperSettingsBackedByCVars.h"

#include "AtumSettings.generated.h"


#define LOCTEXT_NAMESPACE "AtumSettings"

UCLASS(MinimalAPI, Config = "Atum", Blueprintable, BlueprintType, DisplayName = "ATUM Settings")
class UAtumSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Developer", meta = (
		AllowPrivateAccess,
		ConsoleVariable = "atum.Settings.Logging"
	))
	bool bLogging;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Editor", meta = (
		AllowPrivateAccess,
		ConfigRestartRequired = "true"
	))
	FColor NeuralNetworkAssetTypeColor;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Editor", meta = (
		AllowPrivateAccess,
		ConsoleVariable = "atum.Settings.AllowBlueprintableClasses"
	))
	bool bAllowBlueprintableClasses;
	
public:
	UE_NODISCARD_CTOR
	UAtumSettings() noexcept;
	
protected:
	void RegisterConsoleVariables() noexcept;
	
public:
	UE_NODISCARD
	FORCEINLINE bool IsLogging() const noexcept { return bLogging; }
	
	UE_NODISCARD
	FORCEINLINE void SetLogging(const bool bValue) noexcept { bLogging = bValue; }
	
	UE_NODISCARD
	FORCEINLINE FColor GetNeuralNetworkAssetTypeColor() const noexcept { return NeuralNetworkAssetTypeColor; }
	
	UE_NODISCARD
	FORCEINLINE bool CanAllowBlueprintableClasses() const noexcept { return bAllowBlueprintableClasses; }
	
	UE_NODISCARD
	FORCEINLINE void SetAllowBlueprintableClasses(const bool bValue) noexcept { bAllowBlueprintableClasses = bValue; }
};

#undef LOCTEXT_NAMESPACE
