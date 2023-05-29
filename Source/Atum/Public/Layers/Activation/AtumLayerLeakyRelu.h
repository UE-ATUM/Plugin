// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLeakyReluOptions.h"
#include "IAtumLayerBaseActivation.h"
#include "Macros/AtumMacrosLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/activation.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLeakyRelu.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLeakyRelu"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Leaky ReLU Layer")
class ATUM_API UAtumLayerLeakyRelu : public UObject, public IAtumLayerBaseActivation
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerLeakyReluOptions, torch::nn::LeakyReLU)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerLeakyReluOptions Options;
};

#undef LOCTEXT_NAMESPACE
