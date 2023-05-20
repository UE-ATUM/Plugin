// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "Layers/IAtumLayerOptions.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/batchnorm.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerBatchNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerBatchNormOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Batch Norm Layer Options")
struct ATUM_API FAtumLayerBatchNormOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 NumFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Epsilon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Momentum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bAffine;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bTrackRunningStats;

	UE_NODISCARD_CTOR
	FAtumLayerBatchNormOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::BatchNormOptions() const noexcept
	{
		return torch::nn::BatchNormOptions(NumFeatures)
		.eps(Epsilon)
		.momentum(Momentum == 0.0 ? c10::nullopt : c10::optional<double>(Momentum))
		.affine(bAffine)
		.track_running_stats(bTrackRunningStats);
	}
};

#undef LOCTEXT_NAMESPACE
