// © 2023 Kaya Adrian.

#include "Layers/Convolution/IAtumLayerConv.h"

#include "IAtum.h"


IAtumLayerConv::IAtumLayerConv() noexcept : DimensionCount(0u)
{
}

bool IAtumLayerConv::AreInputSizesValid(
	const int64 SizeCount,
	const int64 GivenChannels,
	const int64 ExpectedChannels
) const noexcept
{
	if (SizeCount != DimensionCount + 1 && SizeCount != DimensionCount + 2)
	{
		UE_LOG(LogAtum, Error, TEXT("Cannot use %lldD input tensor!"), SizeCount)
		return false;
	}
	
	if (GivenChannels != ExpectedChannels)
	{
		UE_LOG(LogAtum, Error, TEXT("Expected %lld channels but got %lld!"), ExpectedChannels, GivenChannels)
		return false;
	}

	return true;
}
