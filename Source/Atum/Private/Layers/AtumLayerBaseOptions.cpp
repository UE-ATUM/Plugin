// © 2023 Kaya Adrian.

#include "Layers/AtumLayerBaseOptions.h"

#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/module.h>
TORCH_INCLUDES_END


#define LOCTEXT_NAMESPACE "AtumLayerBaseOptions"

FAtumLayerBaseOptions::FAtumLayerBaseOptions() noexcept : LayerName(TEXT("UNNAMED_LAYER"))
{
}

void FAtumLayerBaseOptions::SetNameFrom(const torch::nn::Module& Module) noexcept
{
	LayerName = Module.name().c_str();
}

#undef LOCTEXT_NAMESPACE
