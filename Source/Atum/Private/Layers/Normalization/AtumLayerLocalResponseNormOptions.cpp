// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerLocalResponseNormOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerLocalResponseNormOptions"

FAtumLayerLocalResponseNormOptions::FAtumLayerLocalResponseNormOptions() noexcept :
Size(0LL),
Alpha(1E-4),
Beta(0.75),
K(1.0)
{
}

void FAtumLayerLocalResponseNormOptions::SetFrom(const torch::nn::LocalResponseNormOptions& Options) noexcept
{
	Size = Options.size();
	Alpha = Options.alpha();
	Beta = Options.beta();
	K = Options.k();
}

#undef LOCTEXT_NAMESPACE
