// © 2023 Kaya Adrian.

#include "Layers/Linear/AtumLayerLinearOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerLinearOptions"

FAtumLayerLinearOptions::FAtumLayerLinearOptions() noexcept : InFeatures(0LL), OutFeatures(0LL), bBias(true)
{
}

void FAtumLayerLinearOptions::SetFrom(const torch::nn::LinearOptions& Options) noexcept
{
	InFeatures = Options.in_features();
	OutFeatures = Options.out_features();
	bBias = Options.bias();
}

#undef LOCTEXT_NAMESPACE
