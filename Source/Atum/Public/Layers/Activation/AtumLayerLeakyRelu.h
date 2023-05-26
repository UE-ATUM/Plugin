// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLeakyReluOptions.h"
#include "IAtumLayerBaseActivation.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/activation.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLeakyRelu.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLeakyRelu"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Leaky ReLU Layer")
class ATUM_API UAtumLayerLeakyRelu : public UObject, public IAtumLayerBaseActivation
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::LeakyReLU)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FAtumLayerLeakyReluOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = true) override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerLeakyReluOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerLeakyReluOptions& GetOptions() noexcept { return Options; }
};

#undef LOCTEXT_NAMESPACE
