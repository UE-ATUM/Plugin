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
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Settings", meta = (
		AllowPrivateAccess,
		ConsoleVariable = "atum.Settings.Logging"
	))
	bool bLogging;
	
public:
	UE_NODISCARD_CTOR
	UAtumSettings() noexcept;
	
	UE_NODISCARD
	FORCEINLINE bool IsLogging() const noexcept { return bLogging; }
	
	UE_NODISCARD
	FORCEINLINE void SetLogging(const bool bValue) noexcept { bLogging = bValue; }
};

#undef LOCTEXT_NAMESPACE
