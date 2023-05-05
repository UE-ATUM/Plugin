// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerBatchNormOptions.h"


FAtumLayerBatchNormOptions::FAtumLayerBatchNormOptions() noexcept :
NumFeatures(0),
Epsilon(1e-5),
Momentum(0.1),
bAffine(true),
bTrackRunningStats(true)
{
}

FAtumLayerBatchNormOptions::operator torch::nn::BatchNormOptions() const noexcept
{
	return torch::nn::BatchNormOptions(NumFeatures)
	.eps(Epsilon)
	.momentum(Momentum == 0.0 ? c10::nullopt : c10::optional<double>(Momentum))
	.affine(bAffine)
	.track_running_stats(bTrackRunningStats);
}
