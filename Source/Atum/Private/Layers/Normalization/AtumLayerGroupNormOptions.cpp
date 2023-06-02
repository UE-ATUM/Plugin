// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerGroupNormOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerGroupNormOptions"

FAtumLayerGroupNormOptions::FAtumLayerGroupNormOptions() noexcept :
NumGroups(0LL),
NumChannels(0LL),
Eps(1E-5),
bAffine(true)
{
}

void FAtumLayerGroupNormOptions::SetFrom(const torch::nn::GroupNormOptions& Options) noexcept
{
	NumGroups = Options.num_groups();
	NumChannels = Options.num_channels();
	Eps = Options.eps();
	bAffine = Options.affine();
}

#undef LOCTEXT_NAMESPACE
