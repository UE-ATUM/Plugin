// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerCrossMapLrnOptions.h"
#include "IAtumLayerBaseNormalization.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/normalization.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerCrossMapLrn.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerCrossMapLrn"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Cross Map LRN 2D Layer")
class ATUM_API UAtumLayerCrossMapLrn2D : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::CrossMapLRN2d)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FAtumLayerCrossMapLrnOptions Options;
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerCrossMapLrn2D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = true) noexcept override;

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

#undef LOCTEXT_NAMESPACE
