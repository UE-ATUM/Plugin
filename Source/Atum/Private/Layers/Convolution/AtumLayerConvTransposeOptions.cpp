// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConvTransposeOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerConvTransposeOptions"

FAtumLayerConvTransposeOptions::FAtumLayerConvTransposeOptions(const uint64 Dimensions) noexcept :
InChannels(0LL),
OutChannels(0LL),
Groups(1LL),
bBias(true)
{
	for (uint64 Index = 0ULL; Index < Dimensions; ++Index)
	{
		KernelSize.Add(0LL);
		Stride.Add(1LL);
		Padding.Add(0LL);
		OutputPadding.Add(0LL);
		Dilation.Add(1LL);
	}
}

#undef LOCTEXT_NAMESPACE
