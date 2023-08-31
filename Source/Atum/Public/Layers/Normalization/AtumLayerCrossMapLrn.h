// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerCrossMapLrnOptions.h"
#include "IAtumLayerBaseNormalization.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerCrossMapLrn.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerCrossMapLrn"

/**
 * Cross Map LRN 2D layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Cross Map LRN 2D Layer")
class ATUM_API UAtumLayerCrossMapLrn2D : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerCrossMapLrnOptions, torch::nn::CrossMapLRN2d)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerCrossMapLrnOptions Options;
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerCrossMapLrn2D() noexcept;
};

#undef LOCTEXT_NAMESPACE
