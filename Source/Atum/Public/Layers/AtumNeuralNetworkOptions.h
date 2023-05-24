// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerBaseOptions.h"

#include "AtumNeuralNetworkOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkOptions"

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	struct AtumNetworkOptions
	{
	};
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


USTRUCT(BlueprintType, DisplayName = "ATUM Neural Network Options")
struct ATUM_API FAtumNeuralNetworkOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::AtumNetworkOptions() const noexcept
	{ return torch::nn::AtumNetworkOptions(); }
};

#undef LOCTEXT_NAMESPACE
