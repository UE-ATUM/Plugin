// © 2023 Kaya Adrian.

#pragma once

#include "LibTorch.h"

#include "AtumLayerLinearOptions.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Linear Layer Options")
struct ATUM_API FAtumOptionsLinear
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	int64 InFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	int64 OutFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	bool bBias;

	UE_NODISCARD_CTOR
	FAtumOptionsLinear() noexcept;
	
	UE_NODISCARD
	explicit operator torch::nn::LinearOptions() const noexcept;
};
