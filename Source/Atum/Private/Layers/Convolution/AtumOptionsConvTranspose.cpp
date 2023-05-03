// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumOptionsConvTranspose.h"


namespace
{
	template <uint64 Dimensions>
	requires (1u <= Dimensions && Dimensions <= 3u)
	UE_NODISCARD
	torch::nn::ConvTransposeOptions<Dimensions> CastConvTranspose(const FAtumOptionsConvTranspose& Options) noexcept
	{
		return torch::nn::ConvTransposeOptions<Dimensions>(
			Options.InChannels,
			Options.OutChannels,
			torch::IntArrayRef(Options.KernelSize.GetData(), Dimensions)
		).stride(torch::IntArrayRef(Options.Stride.GetData(), Dimensions))
		.padding(torch::IntArrayRef(Options.Padding.GetData(), Dimensions))
		.output_padding(torch::IntArrayRef(Options.OutputPadding.GetData(), Dimensions))
		.groups(Options.Groups)
		.bias(Options.bBias)
		.dilation(torch::IntArrayRef(Options.Dilation.GetData(), Dimensions))
		.padding_mode(AtumEnums::Cast<Dimensions>(Options.PaddingMode));
	}
}

FAtumOptionsConvTranspose::FAtumOptionsConvTranspose() noexcept : FAtumOptionsConvTranspose(3u)
{
}

FAtumOptionsConvTranspose::FAtumOptionsConvTranspose(const uint64 Dimensions) noexcept :
InChannels(0),
OutChannels(0),
KernelSize(TArray<int64>()),
Stride(TArray<int64>()),
Padding(TArray<int64>()),
OutputPadding(TArray<int64>()),
Groups(1),
bBias(true),
Dilation(TArray<int64>()),
PaddingMode(EAtumConvPaddingMode::Zeros)
{
	for (uint64 Index = 0u; Index < Dimensions; ++Index)
	{
		Stride.Add(1);
		Padding.Add(0);
		OutputPadding.Add(0);
		Dilation.Add(1);
	}
}

FAtumOptionsConvTranspose::operator torch::nn::ConvTranspose1dOptions() const noexcept
{
	return CastConvTranspose<1u>(*this);
}

FAtumOptionsConvTranspose::operator torch::nn::ConvTranspose2dOptions() const noexcept
{
	return CastConvTranspose<2u>(*this);
}

FAtumOptionsConvTranspose::operator torch::nn::ConvTranspose3dOptions() const noexcept
{
	return CastConvTranspose<3u>(*this);
}
