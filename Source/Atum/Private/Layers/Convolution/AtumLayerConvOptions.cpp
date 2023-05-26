// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConvOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerConvOptions"

FAtumLayerConvOptions::FAtumLayerConvOptions(const uint64 Dimensions) noexcept :
InChannels(0LL),
OutChannels(0LL),
Groups(1LL),
bBias(true),
PaddingMode(EAtumConvPaddingMode::Zeros)
{
	for (uint64 Index = 0ULL; Index < Dimensions; ++Index)
	{
		KernelSize.Add(0LL);
		Stride.Add(1LL);
		Padding.Add(0LL);
		Dilation.Add(1LL);
	}
}

#undef LOCTEXT_NAMESPACE
