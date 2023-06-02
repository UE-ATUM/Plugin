// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/functional/instancenorm.h>
TORCH_INCLUDES_END

#include "AtumLayerInstanceNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerInstanceNormOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Instance Norm Layer Options")
struct ATUM_API FAtumLayerInstanceNormOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 NumFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Eps;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Momentum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bAffine;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bTrackRunningStats;
	
	UE_NODISCARD_CTOR
	FAtumLayerInstanceNormOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::InstanceNormOptions() const noexcept
	{
		return torch::nn::InstanceNormOptions(NumFeatures)
		.eps(Eps)
		.momentum(Momentum)
		.affine(bAffine)
		.track_running_stats(bTrackRunningStats);
	}
	
	void SetFrom(const torch::nn::InstanceNormOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
