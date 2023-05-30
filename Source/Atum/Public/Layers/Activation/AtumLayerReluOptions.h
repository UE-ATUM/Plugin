// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/activation.h>
TORCH_INCLUDES_END

#include "AtumLayerReluOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerReluOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM ReLU Layer Options")
struct ATUM_API FAtumLayerReluOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bInplace;
	
	UE_NODISCARD_CTOR
	FAtumLayerReluOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::ReLUOptions() const noexcept { return torch::nn::ReLUOptions(bInplace); }
};

#undef LOCTEXT_NAMESPACE
