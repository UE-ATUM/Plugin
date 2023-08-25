// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/rnn.h>
TORCH_INCLUDES_END

#include "AtumLayerLstmOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLstmOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM LSTM Layer Options")
struct ATUM_API FAtumLayerLstmOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 InputSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 HiddenSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 LayerCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bBias;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bBatchFirst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Dropout;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bBidirectional;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 ProjectionSize;
	
	UE_NODISCARD_CTOR
	FAtumLayerLstmOptions() noexcept;
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::LSTMOptions() const noexcept
	{
		return torch::nn::LSTMOptions(InputSize, HiddenSize)
		.num_layers(LayerCount)
		.bias(bBias)
		.batch_first(bBatchFirst)
		.dropout(Dropout)
		.bidirectional(bBidirectional)
		.proj_size(ProjectionSize);
	}
	
	void SetFrom(const torch::nn::LSTMOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
