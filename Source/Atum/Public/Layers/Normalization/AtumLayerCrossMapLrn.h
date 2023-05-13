// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerCrossMapLrnOptions.h"
#include "IAtumLayerBaseNorm.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerCrossMapLrn.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Cross Map LRN 2D Layer")
class ATUM_API UAtumLayerCrossMapLrn2D : public UObject, public IAtumLayerBaseNorm,
public TAtumLayer<torch::nn::CrossMapLRN2dImpl>
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerCrossMapLrnOptions Options;
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerCrossMapLrn2D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerCrossMapLrnOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerCrossMapLrnOptions& GetOptions() noexcept { return Options; }
};
