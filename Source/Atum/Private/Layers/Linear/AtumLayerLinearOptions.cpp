// © 2023 Kaya Adrian.

#include "Layers/Linear/AtumLayerLinearOptions.h"


FAtumOptionsLinear::FAtumOptionsLinear() noexcept : InFeatures(0), OutFeatures(0), bBias(true)
{
}

FAtumOptionsLinear::operator torch::nn::LinearOptions() const noexcept
{
	return torch::nn::LinearOptions(InFeatures, OutFeatures).bias(bBias);
}
