﻿// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerLayerNormOptions.h"


FAtumLayerLayerNormOptions::FAtumLayerLayerNormOptions() noexcept :
NormalizedShape(TArray<int64>()),
Epsilon(1e-5),
bElementwiseAffine(true)
{
}

FAtumLayerLayerNormOptions::operator torch::nn::LayerNormOptions() const noexcept
{
	const int64* const Data = NormalizedShape.GetData();
	return MoveTemp(
		torch::nn::LayerNormOptions(std::vector(Data, Data + NormalizedShape.Num()))
		.eps(Epsilon)
		.elementwise_affine(bElementwiseAffine)
	);
}