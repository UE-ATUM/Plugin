// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "Layers/IAtumLayerOptions.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerCrossMapLrnOptions.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Cross Map LRN Layer Options")
struct ATUM_API FAtumLayerCrossMapLrnOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 Size;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Alpha;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Beta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 K;
	
	UE_NODISCARD_CTOR
	FAtumLayerCrossMapLrnOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::CrossMapLRN2dOptions() const noexcept
	{ return torch::nn::CrossMapLRN2dOptions(Size).alpha(Alpha).beta(Beta).k(K); }
};
