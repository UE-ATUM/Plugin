// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/linear.h>
TORCH_INCLUDES_END

#include "AtumLayerFlattenOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerFlattenOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Flatten Layer Options")
struct ATUM_API FAtumLayerFlattenOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 StartDimension;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 EndDimension;
	
	UE_NODISCARD_CTOR
	FAtumLayerFlattenOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::FlattenOptions() const noexcept
	{ return torch::nn::FlattenOptions().start_dim(StartDimension).end_dim(EndDimension); }
	
	void SetFrom(const torch::nn::FlattenOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
