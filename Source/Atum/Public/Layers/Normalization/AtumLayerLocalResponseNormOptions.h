// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLocalResponseNormOptions.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Local Response Norm Layer Options")
struct ATUM_API FAtumLayerLocalResponseNormOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 Size;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Alpha;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Beta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double K;
	
	UE_NODISCARD_CTOR
	FAtumLayerLocalResponseNormOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::LocalResponseNormOptions() const noexcept
	{ return torch::nn::LocalResponseNormOptions(Size).alpha(Alpha).beta(Beta).k(K); }
};
