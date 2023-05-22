// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "Layers/IAtumLayerOptions.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/activation.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerReluOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerReluOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM ReLU Layer Options")
struct ATUM_API FAtumLayerReluOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bInplace;

	UE_NODISCARD_CTOR
	FAtumLayerReluOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::ReLUOptions() const noexcept { return torch::nn::ReLUOptions(bInplace); }
};

#undef LOCTEXT_NAMESPACE
