// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerInstanceNormOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerInstanceNormOptions"

FAtumLayerInstanceNormOptions::FAtumLayerInstanceNormOptions() noexcept :
NumFeatures(0LL),
Eps(1E-5),
Momentum(0.1),
bAffine(false),
bTrackRunningStats(false)
{
}

void FAtumLayerInstanceNormOptions::SetFrom(const torch::nn::InstanceNormOptions& Options) noexcept
{
	NumFeatures = Options.num_features();
	Eps = Options.eps();
	Momentum = Options.momentum();
	bAffine = Options.affine();
	bTrackRunningStats = Options.track_running_stats();
}

#undef LOCTEXT_NAMESPACE
