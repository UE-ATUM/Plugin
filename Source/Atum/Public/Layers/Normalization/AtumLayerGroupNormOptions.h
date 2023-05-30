// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerGroupNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerGroupNormOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Group Norm Layer Options")
struct ATUM_API FAtumLayerGroupNormOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 NumGroups;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 NumChannels;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Eps;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bAffine;
	
	UE_NODISCARD_CTOR
	FAtumLayerGroupNormOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::GroupNormOptions() const noexcept
	{ return torch::nn::GroupNormOptions(NumGroups, NumChannels).eps(Eps).affine(bAffine); }
};

#undef LOCTEXT_NAMESPACE
