// © 2023 Kaya Adrian.

#pragma once

#include "IAtum.h"
#include "LibTorch.h"

#include "AtumLayerConvPaddingMode.generated.h"


UENUM(BlueprintType, Category = "ATUM|Conv", DisplayName = "ATUM Conv Padding Mode", meta = (
	Keywords = "ATUM Conv Padding Mode"
))
enum class EAtumConvPaddingMode : uint8
{
	Zeros UMETA(DisplayName = "Zeros"), // kZeros
	Reflect UMETA(DisplayName = "Reflect"), // kReflect
	Replicate UMETA(DisplayName = "Replicate"), // kReplicate
	Circular UMETA(DisplayName = "Circular") // kCircular
};


namespace AtumEnums
{
	template <uint64 Dimensions>
	requires (1u <= Dimensions && Dimensions <= 3u)
	UE_NODISCARD
	static CONSTEXPR typename torch::nn::ConvTransposeOptions<Dimensions>::padding_mode_t Cast(
		const EAtumConvPaddingMode ConvPaddingMode
	) noexcept
	{
		switch (ConvPaddingMode)
		{
		case EAtumConvPaddingMode::Zeros:
			return torch::kZeros;
			
		case EAtumConvPaddingMode::Reflect:
			return torch::kReflect;
			
		case EAtumConvPaddingMode::Replicate:
			return torch::kReplicate;
			
		case EAtumConvPaddingMode::Circular:
			return torch::kCircular;
			
		default:
			UE_LOG(LogAtum, Error, TEXT("Unknown ConvPaddingMode: %hhd"), ConvPaddingMode)
			return torch::kZeros;
		}
	}

	template <uint64 Dimensions>
	requires (1u <= Dimensions && Dimensions <= 3u)
	UE_NODISCARD
	static CONSTEXPR EAtumConvPaddingMode Cast(
		const typename torch::nn::ConvTransposeOptions<Dimensions>::padding_mode_t ConvPaddingMode
	) noexcept
	{
		switch (CONSTEXPR uint64 Index = ConvPaddingMode.index())
		{
		case 0u:
			return EAtumConvPaddingMode::Zeros;
			
		case 1u:
			return EAtumConvPaddingMode::Reflect;
			
		case 2u:
			return EAtumConvPaddingMode::Replicate;
			
		case 3u:
			return EAtumConvPaddingMode::Circular;
			
		default:
			UE_LOG(LogAtum, Error, TEXT("Unknown ConvPaddingMode: %llu"), Index)
			return EAtumConvPaddingMode::Zeros;
		}
	}
}
