// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLocalResponseNormOptions.h"
#include "IAtumLayerBaseNorm.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLocalResponseNorm.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Local Response Norm Layer")
class ATUM_API UAtumLayerLocalResponseNorm : public UObject, public IAtumLayerBaseNorm,
public TAtumLayer<torch::nn::LocalResponseNormImpl>
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerLocalResponseNormOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerLocalResponseNormOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerLocalResponseNormOptions& GetOptions() noexcept { return Options; }
};
