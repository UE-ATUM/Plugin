// © 2023 Kaya Adrian.

#pragma once

#include "IAtum.h"
#include "LibTorchPreSetup.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/options/conv.h>
LIBTORCH_INCLUDES_END

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
	template <uint64 Dimensions = 1u>
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

	template <uint64 Dimensions = 1u>
	requires (1u <= Dimensions && Dimensions <= 3u)
	UE_NODISCARD
	static CONSTEXPR EAtumConvPaddingMode Cast(
		const typename torch::nn::ConvTransposeOptions<Dimensions>::padding_mode_t ConvPaddingMode
	) noexcept
	{
		if CONSTEXPR (c10::get_if<torch::enumtype::kZeros>(ConvPaddingMode))
			return EAtumConvPaddingMode::Zeros;
		else if CONSTEXPR (c10::get_if<torch::enumtype::kReflect>(ConvPaddingMode))
			return EAtumConvPaddingMode::Reflect;
		else if CONSTEXPR (c10::get_if<torch::enumtype::kReplicate>(ConvPaddingMode))
			return EAtumConvPaddingMode::Replicate;
		else if CONSTEXPR (c10::get_if<torch::enumtype::kCircular>(ConvPaddingMode))
			return EAtumConvPaddingMode::Circular;
		
		UE_LOG(
			LogAtum,
			Error,
			TEXT("Unknown ConvPaddingMode: %hs"),
			torch::enumtype::get_enum_name(ConvPaddingMode).c_str()
		)
		return EAtumConvPaddingMode::Zeros;
	}
}
