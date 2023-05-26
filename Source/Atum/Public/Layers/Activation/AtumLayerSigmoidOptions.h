// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"

#include "AtumLayerSigmoidOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerSigmoidOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Sigmoid Layer Options")
struct ATUM_API FAtumLayerSigmoidOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
};

#undef LOCTEXT_NAMESPACE
