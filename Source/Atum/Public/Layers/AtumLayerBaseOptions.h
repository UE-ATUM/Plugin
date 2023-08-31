// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerBaseOptions.generated.h"

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	class Module;
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


#define LOCTEXT_NAMESPACE "AtumLayerBaseOptions"

/**
 * Base options structure for layers
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Layer Base Options")
struct ATUM_API FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Name of this layer for debugging purposes
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FString LayerName;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerBaseOptions() noexcept;
	
	/**
	 * Sets the layer's name from a module
	 * 
	 * @param Module LibTorch-equivalent module instance
	 */
	void SetNameFrom(const torch::nn::Module& Module) noexcept;
};

#undef LOCTEXT_NAMESPACE
