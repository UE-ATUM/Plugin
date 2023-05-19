// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "Layers/IAtumLayerOptions.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLayerNormOptions.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Layer Norm Layer Options")
struct ATUM_API FAtumLayerLayerNormOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> NormalizedShape;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Epsilon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bElementwiseAffine;
	
	UE_NODISCARD_CTOR
	FAtumLayerLayerNormOptions() noexcept;
	
	UE_NODISCARD
	explicit operator torch::nn::LayerNormOptions() const noexcept;
};
