// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConvTransposeOptions.h"


FAtumLayerConvTransposeOptions::FAtumLayerConvTransposeOptions() noexcept : FAtumLayerConvTransposeOptions(3u)
{
}

FAtumLayerConvTransposeOptions::FAtumLayerConvTransposeOptions(const uint64 Dimensions) noexcept :
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
		KernelSize.Add(0);
		Stride.Add(1);
		Padding.Add(0);
		OutputPadding.Add(0);
		Dilation.Add(1);
	}
}
