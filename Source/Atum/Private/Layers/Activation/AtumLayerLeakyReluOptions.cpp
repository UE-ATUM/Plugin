// © 2023 Kaya Adrian.

#include "Layers/Activation/AtumLayerLeakyReluOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerLeakyReluOptions"

FAtumLayerLeakyReluOptions::FAtumLayerLeakyReluOptions() noexcept : NegativeSlope(1E-2), bInplace(false)
{
}

void FAtumLayerLeakyReluOptions::SetFrom(const torch::nn::LeakyReLUOptions& Options) noexcept
{
	NegativeSlope = Options.negative_slope();
	bInplace = Options.inplace();
}

#undef LOCTEXT_NAMESPACE
