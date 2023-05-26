// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerSigmoidOptions.h"
#include "AtumMacros.h"
#include "IAtumLayerBaseActivation.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/activation.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerSigmoid.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerSigmoid"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Sigmoid Layer")
class ATUM_API UAtumLayerSigmoid : public UObject, public IAtumLayerBaseActivation
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::Sigmoid)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FAtumLayerSigmoidOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = true) override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerSigmoidOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerSigmoidOptions& GetOptions() noexcept { return Options; }
};

#undef LOCTEXT_NAMESPACE
