// © 2023 Kaya Adrian.

#include "Layers/Convolution/IAtumLayerBaseConvolution.h"

#include "AtumMacros.h"
#include "AtumSettings.h"


#define LOCTEXT_NAMESPACE "IAtumLayerBaseConvolution"

bool IAtumLayerBaseConvolution::AreChannelsDivisibleByGroups(
	const int64 InChannels,
	const int64 OutChannels,
	const int64 Groups
) noexcept
{
	bool bPositiveValues = true;
	if (Groups <= 0LL)
	{
		ATUM_LOG(Error, TEXT("There must exist at least 1 group!"))
		bPositiveValues = false;
	}
	if (InChannels <= 0LL)
	{
		ATUM_LOG(Error, TEXT("There must exist at least 1 input channel!"))
		bPositiveValues = false;
	}
	if (OutChannels <= 0LL)
	{
		ATUM_LOG(Error, TEXT("There must exist at least 1 output channel!"))
		bPositiveValues = false;
	}
	if (!bPositiveValues)
		return false;
	
	if (InChannels % Groups != 0LL || OutChannels % Groups != 0LL)
	{
		ATUM_LOG(Error, TEXT("Input and output channels must both be divisible by the group count!"))
		return false;
	}

	return true;
}

bool IAtumLayerBaseConvolution::AreSizesPositive(
	const TArray<int64>& Sizes,
	const FString& Name,
	const bool bAllowZero
) const noexcept
{
	if (bAllowZero)
	{
		for (uint64 Index = 0ULL; Index < DimensionCount; ++Index)
		{
			if (Sizes[Index] < 0LL)
			{
				ATUM_LOG(Error, TEXT("%ls cannot be composed of negative integers!"), *Name)
				return false;
			}
		}
	}
	else
	{
		for (uint64 Index = 0ULL; Index < DimensionCount; ++Index)
		{
			if (Sizes[Index] <= 0LL)
			{
				ATUM_LOG(Error, TEXT("%ls must be composed of positive integers!"), *Name)
				return false;
			}
		}
	}
	
	return true;
}

#undef LOCTEXT_NAMESPACE
