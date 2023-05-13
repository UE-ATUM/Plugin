// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerGroupNormOptions.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Group Norm Layer Options")
struct ATUM_API FAtumLayerGroupNormOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 NumGroups;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 NumChannels;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Eps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bAffine;
	
	UE_NODISCARD_CTOR
	FAtumLayerGroupNormOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::GroupNormOptions() const noexcept
	{ return torch::nn::GroupNormOptions(NumGroups, NumChannels).eps(Eps).affine(bAffine); }
};
