// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"

#include "AtumLayerTanhOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerTanhOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Tanh Layer Options")
struct ATUM_API FAtumLayerTanhOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
};

#undef LOCTEXT_NAMESPACE
