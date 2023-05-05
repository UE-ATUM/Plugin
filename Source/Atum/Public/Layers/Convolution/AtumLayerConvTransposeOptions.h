// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvPaddingMode.h"

#include "AtumLayerConvTransposeOptions.generated.h"

class UAtumLayerConvTranspose;


USTRUCT(BlueprintType, DisplayName = "ATUM Conv Transpose Layer Options")
struct ATUM_API FAtumLayerConvTransposeOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 InChannels;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 OutChannels;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> KernelSize;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> Stride;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> Padding;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> OutputPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 Groups;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bBias;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> Dilation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	EAtumConvPaddingMode PaddingMode;
	
protected:
	UE_NODISCARD_CTOR
	FAtumLayerConvTransposeOptions() noexcept;

public:
	UE_NODISCARD_CTOR
	explicit FAtumLayerConvTransposeOptions(uint64 Dimensions) noexcept;

protected:
	template <uint64 Dimensions>
	requires (1u <= Dimensions && Dimensions <= 3u)
	UE_NODISCARD
	torch::nn::ConvTransposeOptions<Dimensions> CastConvTranspose() const noexcept;
	
public:
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::ConvTranspose1dOptions() const noexcept { return CastConvTranspose<1>(); }

	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::ConvTranspose2dOptions() const noexcept { return CastConvTranspose<2>(); }
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::ConvTranspose3dOptions() const noexcept { return CastConvTranspose<3>(); }

	friend UAtumLayerConvTranspose;
	friend UScriptStruct;
};


template <uint64 Dimensions>
requires (1u <= Dimensions && Dimensions <= 3u)
torch::nn::ConvTransposeOptions<Dimensions> FAtumLayerConvTransposeOptions::CastConvTranspose() const noexcept
{
	return torch::nn::ConvTransposeOptions<Dimensions>(
		InChannels,
		OutChannels,
		torch::IntArrayRef(KernelSize.GetData(), Dimensions)
	).stride(torch::IntArrayRef(Stride.GetData(), Dimensions))
	.padding(torch::IntArrayRef(Padding.GetData(), Dimensions))
	.output_padding(torch::IntArrayRef(OutputPadding.GetData(), Dimensions))
	.groups(Groups)
	.bias(bBias)
	.dilation(torch::IntArrayRef(Dilation.GetData(), Dimensions))
	.padding_mode(AtumEnums::Cast<Dimensions>(PaddingMode));
}
