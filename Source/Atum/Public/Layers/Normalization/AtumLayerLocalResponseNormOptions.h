﻿// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerLocalResponseNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLocalResponseNormOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Local Response Norm Layer Options")
struct ATUM_API FAtumLayerLocalResponseNormOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 Size;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Alpha;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Beta;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double K;
	
	UE_NODISCARD_CTOR
	FAtumLayerLocalResponseNormOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::LocalResponseNormOptions() const noexcept
	{ return torch::nn::LocalResponseNormOptions(Size).alpha(Alpha).beta(Beta).k(K); }
	
	void SetFrom(const torch::nn::LocalResponseNormOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
