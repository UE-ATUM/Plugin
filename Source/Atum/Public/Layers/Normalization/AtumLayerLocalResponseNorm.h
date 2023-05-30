// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLocalResponseNormOptions.h"
#include "IAtumLayerBaseNormalization.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerLocalResponseNorm.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLocalResponseNorm"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Local Response Norm Layer")
class ATUM_API UAtumLayerLocalResponseNorm : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerLocalResponseNormOptions, torch::nn::LocalResponseNorm)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerLocalResponseNormOptions Options;
};

#undef LOCTEXT_NAMESPACE
