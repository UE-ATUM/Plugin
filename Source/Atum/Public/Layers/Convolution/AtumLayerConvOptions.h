// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvPaddingMode.h"
#include "Layers/AtumLayerBaseOptions.h"

#include "AtumLayerConvOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerConvOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Conv Layer Options")
struct ATUM_API FAtumLayerConvOptions : public FAtumLayerBaseOptions
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 Groups;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bBias;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> Dilation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	EAtumConvPaddingMode PaddingMode;
	
	UE_NODISCARD_CTOR
	explicit FAtumLayerConvOptions(uint64 Dimensions = 0ULL) noexcept;
	
	template <uint64 Dimensions>
	requires (1ULL <= Dimensions && Dimensions <= 3ULL)
	UE_NODISCARD
	explicit operator torch::nn::ConvOptions<Dimensions>() const noexcept;
	
	template <uint64 Dimensions>
	requires (1ULL <= Dimensions && Dimensions <= 3ULL)
	void SetFrom(const torch::nn::detail::ConvNdOptions<Dimensions>& Options) noexcept;
};


template <uint64 Dimensions>
requires (1ULL <= Dimensions && Dimensions <= 3ULL)
FAtumLayerConvOptions::operator torch::nn::ConvOptions<Dimensions>() const noexcept
{
	checkf(KernelSize.Num() == Dimensions, TEXT("Kernel size must contain exactly %ull values!"), Dimensions)
	checkf(Stride.Num() == Dimensions, TEXT("Stride must contain exactly %ull values!"), Dimensions)
	checkf(Padding.Num() == Dimensions, TEXT("Padding must contain exactly %ull values!"), Dimensions)
	checkf(Dilation.Num() == Dimensions, TEXT("Dilation must contain exactly %ull values!"), Dimensions)
	
	return torch::nn::ConvOptions<Dimensions>(
		InChannels,
		OutChannels,
		at::IntArrayRef(KernelSize.GetData(), Dimensions)
	).stride(at::IntArrayRef(Stride.GetData(), Dimensions))
	.padding(at::IntArrayRef(Padding.GetData(), Dimensions))
	.groups(Groups)
	.bias(bBias)
	.dilation(at::IntArrayRef(Dilation.GetData(), Dimensions))
	.padding_mode(AtumEnums::Cast<Dimensions>(PaddingMode));
}

template <uint64 Dimensions>
requires (1ULL <= Dimensions && Dimensions <= 3ULL)
void FAtumLayerConvOptions::SetFrom(const torch::nn::detail::ConvNdOptions<Dimensions>& Options) noexcept
{
	checkf(KernelSize.Num() == Dimensions, TEXT("Kernel size must contain exactly %ull values!"), Dimensions)
	checkf(Stride.Num() == Dimensions, TEXT("Stride must contain exactly %ull values!"), Dimensions)
	checkf(Padding.Num() == Dimensions, TEXT("Padding must contain exactly %ull values!"), Dimensions)
	checkf(Dilation.Num() == Dimensions, TEXT("Dilation must contain exactly %ull values!"), Dimensions)
	
	InChannels = Options.in_channels();
	OutChannels = Options.out_channels();
	Groups = Options.groups();
	bBias = Options.bias();
	PaddingMode = AtumEnums::Cast<Dimensions>(Options.padding_mode());
	
	for (uint64 Index = 0ULL; Index < Dimensions; ++Index)
	{
		KernelSize[Index] = Options.kernel_size()->at(Index);
		Stride[Index] = Options.stride()->at(Index);
		Padding[Index] = c10::get<torch::ExpandingArray<Dimensions>>(Options.padding())->at(Index);
		Dilation[Index] = Options.dilation()->at(Index);
	}
}

#undef LOCTEXT_NAMESPACE
