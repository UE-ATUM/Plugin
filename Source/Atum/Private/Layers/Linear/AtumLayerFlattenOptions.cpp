// © 2023 Kaya Adrian.

#include "Layers/Linear/AtumLayerFlattenOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerFlattenOptions"

FAtumLayerFlattenOptions::FAtumLayerFlattenOptions() noexcept : StartDimension(1LL), EndDimension(1LL)
{
}

void FAtumLayerFlattenOptions::SetFrom(const torch::nn::FlattenOptions& Options) noexcept
{
	StartDimension = Options.start_dim();
	EndDimension = Options.end_dim();
}

#undef LOCTEXT_NAMESPACE
