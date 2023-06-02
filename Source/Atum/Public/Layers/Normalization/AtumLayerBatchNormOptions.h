// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/batchnorm.h>
TORCH_INCLUDES_END

#include "AtumLayerBatchNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerBatchNormOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Batch Norm Layer Options")
struct ATUM_API FAtumLayerBatchNormOptions : public FAtumLayerBaseOptions
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
	FAtumLayerBatchNormOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::BatchNormOptions() const noexcept
	{
		return torch::nn::BatchNormOptions(NumFeatures)
		.eps(Eps)
		.momentum(Momentum == 0.0 ? c10::nullopt : c10::optional<double>(Momentum))
		.affine(bAffine)
		.track_running_stats(bTrackRunningStats);
	}
	
	void SetFrom(const torch::nn::BatchNormOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
