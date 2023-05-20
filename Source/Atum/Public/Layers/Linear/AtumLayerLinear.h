// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLinearOptions.h"
#include "Layers/IAtumLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/linear.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLinear.generated.h"

class IAtumTensor;


#define LOCTEXT_NAMESPACE "AtumLayerLinear"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Linear Layer")
class ATUM_API UAtumLayerLinear : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::Linear)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerLinearOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerLinearOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerLinearOptions& GetOptions() noexcept { return Options; }
};

#undef LOCTEXT_NAMESPACE
