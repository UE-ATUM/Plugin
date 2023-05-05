// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

#include "AtumLayerInstanceNormOptions.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Instance Norm Layer Options")
struct ATUM_API FAtumLayerInstanceNormOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 NumFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Epsilon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Momentum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bAffine;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bTrackRunningStats;

	UE_NODISCARD_CTOR
	FAtumLayerInstanceNormOptions() noexcept;
	
	UE_NODISCARD
	explicit operator torch::nn::InstanceNormOptions() const noexcept;
};
