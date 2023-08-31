// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerFlattenOptions.h"
#include "Layers/IAtumLayer.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/linear.h>
TORCH_INCLUDES_END

#include "AtumLayerFlatten.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerFlatten"

/**
 * Flatten layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Flatten Layer")
class ATUM_API UAtumLayerFlatten : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerFlattenOptions, torch::nn::Flatten)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerFlattenOptions Options;
};

#undef LOCTEXT_NAMESPACE
