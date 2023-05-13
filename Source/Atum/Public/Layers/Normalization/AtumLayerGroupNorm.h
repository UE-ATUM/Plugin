﻿// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerGroupNormOptions.h"
#include "IAtumLayerBaseNorm.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerGroupNorm.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Group Norm Layer")
class ATUM_API UAtumLayerGroupNorm : public UObject, public IAtumLayerBaseNorm,
public TAtumLayer<torch::nn::GroupNormImpl>
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerGroupNormOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerGroupNormOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerGroupNormOptions& GetOptions() noexcept { return Options; }
};