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

USTRUCT(BlueprintType, DisplayName = "ATUM Layer Base Options")
struct ATUM_API FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FString LayerName;
	
	UE_NODISCARD_CTOR
	FAtumLayerBaseOptions() noexcept;
	
	void SetNameFrom(const torch::nn::Module& Module) noexcept;
};

#undef LOCTEXT_NAMESPACE
