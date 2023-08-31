// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerSigmoidOptions.h"
#include "IAtumLayerBaseActivation.h"
#include "Macros/AtumMacrosGuards.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/activation.h>
TORCH_INCLUDES_END

#include "AtumLayerSigmoid.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerSigmoid"

/**
 * Sigmoid layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Sigmoid Layer")
class ATUM_API UAtumLayerSigmoid : public UObject, public IAtumLayerBaseActivation
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerSigmoidOptions, torch::nn::Sigmoid)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerSigmoidOptions Options;
};

#undef LOCTEXT_NAMESPACE
