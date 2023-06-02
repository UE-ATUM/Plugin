// © 2023 Kaya Adrian.

#pragma once

#include "Macros/AtumMacrosGuards.h"
#include "Optimizers/AtumOptimizerBaseOptions.h"

TORCH_INCLUDES_START
#include <torch/optim/adam.h>
TORCH_INCLUDES_END

#include "AtumOptimizerAdamOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumOptimizerAdamOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Adam Optimizer Options")
struct ATUM_API FAtumOptimizerAdamOptions : public FAtumOptimizerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Lr;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<double> Betas;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Eps;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double WeightDecay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool Amsgrad;
	
	UE_NODISCARD_CTOR
	FAtumOptimizerAdamOptions() noexcept;
	
	UE_NODISCARD
	explicit operator torch::optim::AdamOptions() const noexcept;
	
	void SetFrom(const torch::optim::AdamOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
