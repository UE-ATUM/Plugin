// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConvOptions.h"


FAtumLayerConvOptions::FAtumLayerConvOptions() noexcept : FAtumLayerConvOptions(3u)
{
}

FAtumLayerConvOptions::FAtumLayerConvOptions(const uint64 Dimensions) noexcept :
InChannels(0),
OutChannels(0),
Groups(1),
bBias(true),
PaddingMode(EAtumConvPaddingMode::Zeros)
{
	for (uint64 Index = 0u; Index < Dimensions; ++Index)
	{
		KernelSize.Add(0);
		Stride.Add(1);
		Padding.Add(0);
		Dilation.Add(1);
	}
}
