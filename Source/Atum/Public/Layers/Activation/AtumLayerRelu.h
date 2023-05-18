// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerReluOptions.h"
#include "AtumMacros.h"
#include "IAtumLayerBaseActivation.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/activation.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerRelu.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM ReLU Layer")
class ATUM_API UAtumLayerRelu : public UObject, public IAtumLayerBaseActivation
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::ReLU)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerReluOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerReluOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerReluOptions& GetOptions() noexcept { return Options; }
};
