// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerInstanceNormOptions.h"


FAtumLayerInstanceNormOptions::FAtumLayerInstanceNormOptions() noexcept :
NumFeatures(0),
Epsilon(1e-5),
Momentum(0.1),
bAffine(false),
bTrackRunningStats(false)
{
}

FAtumLayerInstanceNormOptions::operator torch::nn::InstanceNormOptions() const noexcept
{
	return torch::nn::InstanceNormOptions(NumFeatures)
	.eps(Epsilon)
	.momentum(Momentum)
	.affine(bAffine)
	.track_running_stats(bTrackRunningStats);
}
