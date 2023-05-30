// © 2023 Kaya Adrian.

#pragma once

#include "Engine/DeveloperSettingsBackedByCVars.h"

#include "AtumSettingsBase.generated.h"


#define LOCTEXT_NAMESPACE "AtumSettingsBase"

/**
 * @brief Base class for ATUM settings
 */
UCLASS(Abstract, MinimalAPI, Config = "Atum", Blueprintable, BlueprintType, DisplayName = "ATUM Base Settings")
class UAtumSettingsBase : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()
	
public:
	UE_NODISCARD_CTOR
	UAtumSettingsBase() noexcept;
};

#undef LOCTEXT_NAMESPACE
