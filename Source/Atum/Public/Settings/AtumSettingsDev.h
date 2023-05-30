// © 2023 Kaya Adrian.

#pragma once

#include "Settings/AtumSettingsBase.h"

#include "AtumSettingsDev.generated.h"


#define LOCTEXT_NAMESPACE "AtumSettingsDev"

/**
 * @brief ATUM settings for development purposes
 */
UCLASS(MinimalAPI, BlueprintType, DisplayName = "ATUM Dev Settings")
class UAtumSettingsDev : public UAtumSettingsBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, DisplayName = "Enable LogAtum", meta = (
		AllowPrivateAccess,
		ConsoleVariable = "atum.Dev.EnableLogAtum"
	))
	bool bLogAtumEnabled;
	
public:
	UE_NODISCARD_CTOR
	UAtumSettingsDev() noexcept;
	
#if WITH_EDITOR
	UE_NODISCARD
	virtual FText GetSectionText() const override;
	
	UE_NODISCARD
	virtual FText GetSectionDescription() const override;
#endif
	
	UE_NODISCARD
	FORCEINLINE bool IsLogAtumEnabled() const noexcept { return bLogAtumEnabled; }
	
	UE_NODISCARD
	FORCEINLINE void SetLogAtumEnabled(const bool bValue) noexcept { bLogAtumEnabled = bValue; }
};

#undef LOCTEXT_NAMESPACE
