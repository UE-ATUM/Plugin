// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerReluOptions.h"
#include "IAtumLayerBaseActivation.h"
#include "Macros/AtumMacrosLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/activation.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerRelu.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerRelu"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM ReLU Layer")
class ATUM_API UAtumLayerRelu : public UObject, public IAtumLayerBaseActivation
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerReluOptions, torch::nn::ReLU)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FAtumLayerReluOptions Options;
};

#undef LOCTEXT_NAMESPACE
