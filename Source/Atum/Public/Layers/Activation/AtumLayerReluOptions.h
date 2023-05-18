﻿// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/activation.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerReluOptions.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM ReLU Layer Options")
struct ATUM_API FAtumLayerReluOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	bool bInplace;

	UE_NODISCARD_CTOR
	FAtumLayerReluOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::ReLUOptions() const noexcept { return torch::nn::ReLUOptions(bInplace); }
};