﻿// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/activation.h>
TORCH_INCLUDES_END

#include "AtumLayerLeakyReluOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLeakyReluOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Leaky ReLU Layer Options")
struct ATUM_API FAtumLayerLeakyReluOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double NegativeSlope;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bInplace;
	
	UE_NODISCARD_CTOR
	FAtumLayerLeakyReluOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::LeakyReLUOptions() const noexcept
	{ return torch::nn::LeakyReLUOptions().negative_slope(NegativeSlope).inplace(bInplace); }
	
	void SetFrom(const torch::nn::LeakyReLUOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
