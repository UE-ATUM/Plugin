// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "Layers/AtumLayerBaseOptions.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/linear.h>
LIBTORCH_INCLUDES_END

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
};

#undef LOCTEXT_NAMESPACE
