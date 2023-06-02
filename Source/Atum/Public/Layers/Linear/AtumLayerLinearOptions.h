// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/linear.h>
TORCH_INCLUDES_END

#include "AtumLayerLinearOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLinearOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Linear Layer Options")
struct ATUM_API FAtumLayerLinearOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 InFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 OutFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess))
	bool bBias;
	
	UE_NODISCARD_CTOR
	FAtumLayerLinearOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::LinearOptions() const noexcept
	{ return torch::nn::LinearOptions(InFeatures, OutFeatures).bias(bBias); }
	
	void SetFrom(const torch::nn::LinearOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
