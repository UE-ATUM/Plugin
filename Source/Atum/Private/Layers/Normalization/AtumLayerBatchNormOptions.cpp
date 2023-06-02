// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerBatchNormOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerBatchNormOptions"

FAtumLayerBatchNormOptions::FAtumLayerBatchNormOptions() noexcept :
NumFeatures(0LL),
Eps(1E-5),
Momentum(0.1),
bAffine(true),
bTrackRunningStats(true)
{
}

void FAtumLayerBatchNormOptions::SetFrom(const torch::nn::BatchNormOptions& Options) noexcept
{
	NumFeatures = Options.num_features();
	Eps = Options.eps();
	Momentum = Options.momentum().value_or(0.0);
	bAffine = Options.affine();
	bTrackRunningStats = Options.track_running_stats();
}

#undef LOCTEXT_NAMESPACE
