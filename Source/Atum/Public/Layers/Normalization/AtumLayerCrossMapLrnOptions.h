﻿// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerCrossMapLrnOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerCrossMapLrnOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Cross Map LRN Layer Options")
struct ATUM_API FAtumLayerCrossMapLrnOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 Size;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Alpha;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Beta;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 K;
	
	UE_NODISCARD_CTOR
	FAtumLayerCrossMapLrnOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::CrossMapLRN2dOptions() const noexcept
	{ return torch::nn::CrossMapLRN2dOptions(Size).alpha(Alpha).beta(Beta).k(K); }
	
	void SetFrom(const torch::nn::CrossMapLRN2dOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
