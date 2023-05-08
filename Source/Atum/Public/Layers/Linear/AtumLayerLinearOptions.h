// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/linear.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLinearOptions.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Linear Layer Options")
struct ATUM_API FAtumLayerLinearOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	int64 InFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	int64 OutFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	bool bBias;

	UE_NODISCARD_CTOR
	FAtumLayerLinearOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::LinearOptions() const noexcept
	{ return torch::nn::LinearOptions(InFeatures, OutFeatures).bias(bBias); }
};
