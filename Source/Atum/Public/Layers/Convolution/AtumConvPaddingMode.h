// © 2023 Kaya Adrian.

#pragma once

#include "IAtum.h"
#include "LibTorch/LibTorchInclude.h"

#include "AtumConvPaddingMode.generated.h"


UENUM(BlueprintType, Category = "ATUM|Conv", DisplayName = "ATUM Conv Padding Mode", meta = (
	Keywords = "ATUM Conv Padding Mode"
))
enum class EAtumConvPaddingMode : uint8
{
	Zeros UMETA(DisplayName = "Zeros"), // Zeros
	Reflect UMETA(DisplayName = "Reflect"), // Reflect
	Replicate UMETA(DisplayName = "Replicate"), // Replicate
	Circular UMETA(DisplayName = "Circular") // Circular
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
		switch (const uint64 Index = ConvPaddingMode.index())
		{
		case 0:
			return EAtumConvPaddingMode::Zeros;
			
		case 1:
			return EAtumConvPaddingMode::Reflect;
			
		case 2:
			return EAtumConvPaddingMode::Replicate;
			
		case 3:
			return EAtumConvPaddingMode::Circular;
			
		default:
			UE_LOG(LogAtum, Error, TEXT("Unknown ConvPaddingMode: %llu"), Index)
			return EAtumConvPaddingMode::Zeros;
		}
	}
}
