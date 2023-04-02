// © 2023 Kaya Adrian.

#pragma once

#include "Engine/DeveloperSettings.h"

#include "AtumSettings.generated.h"


UCLASS(Config = "Atum", Blueprintable, BlueprintType, DisplayName = "ATUM Settings")
class ATUM_API UAtumSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UAtumSettings();
	
	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
