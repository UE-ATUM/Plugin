// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLinearOptions.h"
#include "Layers/IAtumLayer.h"
#include "Macros/AtumMacrosLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/linear.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLinear.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLinear"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Linear Layer")
class ATUM_API UAtumLayerLinear : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerLinearOptions, torch::nn::Linear)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FAtumLayerLinearOptions Options;
};

#undef LOCTEXT_NAMESPACE
