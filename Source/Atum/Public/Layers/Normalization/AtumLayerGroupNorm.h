// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerGroupNormOptions.h"
#include "IAtumLayerBaseNormalization.h"
#include "Macros/AtumMacrosLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerGroupNorm.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerGroupNorm"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Group Norm Layer")
class ATUM_API UAtumLayerGroupNorm : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerGroupNormOptions, torch::nn::GroupNorm)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FAtumLayerGroupNormOptions Options;
};

#undef LOCTEXT_NAMESPACE
