// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerLayerNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLayerNormOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Layer Norm Layer Options")
struct ATUM_API FAtumLayerLayerNormOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> NormalizedShape;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Eps;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bElementwiseAffine;
	
	UE_NODISCARD_CTOR
	FAtumLayerLayerNormOptions() noexcept;
	
	UE_NODISCARD
	explicit operator torch::nn::LayerNormOptions() const noexcept;
	
	void SetFrom(const torch::nn::LayerNormOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
