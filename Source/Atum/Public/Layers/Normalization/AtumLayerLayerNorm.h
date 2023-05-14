// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLayerNormOptions.h"
#include "IAtumLayerBaseNormalization.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerLayerNorm.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Layer Norm Layer")
class ATUM_API UAtumLayerLayerNorm : public UObject, public IAtumLayerBaseNormalization,
public TAtumLayer<torch::nn::LayerNormImpl>
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerLayerNormOptions Options;

public:
	virtual ~UAtumLayerLayerNorm() noexcept override;

protected:
	void DestroyNormalizedShape() const noexcept;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerLayerNormOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerLayerNormOptions& GetOptions() noexcept { return Options; }
};
