// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerTanhOptions.h"
#include "IAtumLayerBaseActivation.h"
#include "Macros/AtumMacrosGuards.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/activation.h>
TORCH_INCLUDES_END

#include "AtumLayerTanh.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerTanh"

/**
 * Tanh layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Tanh Layer")
class ATUM_API UAtumLayerTanh : public UObject, public IAtumLayerBaseActivation
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerTanhOptions, torch::nn::Tanh)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerTanhOptions Options;
};

#undef LOCTEXT_NAMESPACE
