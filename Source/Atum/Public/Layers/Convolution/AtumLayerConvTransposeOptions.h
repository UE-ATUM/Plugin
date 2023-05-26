// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "Layers/AtumLayerBaseOptions.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/conv.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerConvTransposeOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerConvTransposeOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Conv Transpose Layer Options")
struct ATUM_API FAtumLayerConvTransposeOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 InChannels;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 OutChannels;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> KernelSize;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> Stride;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> Padding;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> OutputPadding;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 Groups;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bBias;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> Dilation;
	
	UE_NODISCARD_CTOR
	explicit FAtumLayerConvTransposeOptions(uint64 Dimensions = 0ULL) noexcept;
	
	template <uint64 Dimensions>
	requires (1ULL <= Dimensions && Dimensions <= 3ULL)
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::ConvTransposeOptions<Dimensions>() const noexcept;
};


template <uint64 Dimensions>
requires (1ULL <= Dimensions && Dimensions <= 3ULL)
FAtumLayerConvTransposeOptions::operator torch::nn::ConvTransposeOptions<Dimensions>() const noexcept
{
	return torch::nn::ConvTransposeOptions<Dimensions>(
		InChannels,
		OutChannels,
		at::IntArrayRef(KernelSize.GetData(), Dimensions)
	).stride(at::IntArrayRef(Stride.GetData(), Dimensions))
	.padding(at::IntArrayRef(Padding.GetData(), Dimensions))
	.output_padding(at::IntArrayRef(OutputPadding.GetData(), Dimensions))
	.groups(Groups)
	.bias(bBias)
	.dilation(at::IntArrayRef(Dilation.GetData(), Dimensions))
	.padding_mode(torch::kZeros);
}

#undef LOCTEXT_NAMESPACE
