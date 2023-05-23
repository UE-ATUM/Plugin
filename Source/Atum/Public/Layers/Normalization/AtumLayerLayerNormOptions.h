// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "Layers/IAtumLayerOptions.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLayerNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLayerNormOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Layer Norm Layer Options")
struct ATUM_API FAtumLayerLayerNormOptions : public FIAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> NormalizedShape;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Epsilon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bElementwiseAffine;
	
	UE_NODISCARD_CTOR
	FAtumLayerLayerNormOptions() noexcept;
	
	UE_NODISCARD
	explicit operator torch::nn::LayerNormOptions() const noexcept;
};

#undef LOCTEXT_NAMESPACE
