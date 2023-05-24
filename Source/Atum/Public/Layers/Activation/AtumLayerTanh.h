// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerTanhOptions.h"
#include "AtumMacros.h"
#include "IAtumLayerBaseActivation.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/activation.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerTanh.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerTanh"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Tanh Layer")
class ATUM_API UAtumLayerTanh : public UObject, public IAtumLayerBaseActivation
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::Tanh)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FAtumLayerTanhOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerTanhOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerTanhOptions& GetOptions() noexcept { return Options; }
};

#undef LOCTEXT_NAMESPACE
