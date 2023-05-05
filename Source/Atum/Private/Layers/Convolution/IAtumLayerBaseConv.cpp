// © 2023 Kaya Adrian.

#include "Layers/Convolution/IAtumLayerBaseConv.h"

#include "IAtum.h"


IAtumLayerBaseConv::IAtumLayerBaseConv() noexcept : DimensionCount(0u)
{
}

bool IAtumLayerBaseConv::AreChannelsDivisibleByGroups(
	const int64 InChannels,
	const int64 OutChannels,
	const int64 Groups
) noexcept
{
	if (Groups <= 0)
	{
		UE_LOG(LogAtum, Error, TEXT("There must exist at least 1 group!"))
		return false;
	}
	if (InChannels % Groups != 0 || OutChannels % Groups != 0)
	{
		UE_LOG(LogAtum, Error, TEXT("Input and output channels must both be divisible by the group count!"))
		return false;
	}

	return true;
}

bool IAtumLayerBaseConv::AreSizesPositive(
	const TArray<int64>& Sizes,
	const FString& Name,
	const bool bAllowZero
) const noexcept
{
	if (bAllowZero)
	{
		for (uint64 Index = 0u; Index < DimensionCount; ++Index)
		{
			if (Sizes[Index] < 0)
			{
				UE_LOG(LogAtum, Error, TEXT("%ls cannot be composed of negative integers!"), *Name)
				return false;
			}
		}
	}
	else
	{
		for (uint64 Index = 0u; Index < DimensionCount; ++Index)
		{
			if (Sizes[Index] <= 0)
			{
				UE_LOG(LogAtum, Error, TEXT("%ls must be composed of positive integers!"), *Name)
				return false;
			}
		}
	}
	
	return true;
}

bool IAtumLayerBaseConv::AreInputSizesValid(
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
