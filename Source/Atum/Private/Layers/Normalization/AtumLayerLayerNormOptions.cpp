// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerLayerNormOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerLayerNormOptions"

FAtumLayerLayerNormOptions::FAtumLayerLayerNormOptions() noexcept : Eps(1E-5), bElementwiseAffine(true)
{
}

FAtumLayerLayerNormOptions::operator torch::nn::LayerNormOptions() const noexcept
{
	const int64* const Data = NormalizedShape.GetData();
	return MoveTemp(
		torch::nn::LayerNormOptions(std::vector(Data, Data + NormalizedShape.Num()))
		.eps(Eps)
		.elementwise_affine(bElementwiseAffine)
	);
}

void FAtumLayerLayerNormOptions::SetFrom(const torch::nn::LayerNormOptions& Options) noexcept
{
	Eps = Options.eps();
	bElementwiseAffine = Options.elementwise_affine();
}

#undef LOCTEXT_NAMESPACE
