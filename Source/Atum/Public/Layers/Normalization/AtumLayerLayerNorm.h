// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLayerNormOptions.h"
#include "IAtumLayerBaseNormalization.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerLayerNorm.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLayerNorm"

/**
 * Structure which deals with destroying the normalised shape vector
 */
struct FNormalizedShapeDeleter
{
	/**
	 * Calls the destructor of the vector as soon as the pointer is deleted
	 * 
	 * @param LayerNorm Pointer to a Layer Normalisation layer
	 */
	void operator()(torch::nn::LayerNorm* LayerNorm) const noexcept;
};


/**
 * Layer Normalisation layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Layer Norm Layer")
class ATUM_API UAtumLayerLayerNorm : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerLayerNormOptions, torch::nn::LayerNorm)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerLayerNormOptions Options;
};

#undef LOCTEXT_NAMESPACE
