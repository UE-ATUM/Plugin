// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvOptions.h"
#include "IAtumLayerBaseConvolution.h"
#include "Macros/AtumMacrosLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/conv.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerConv.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerConv"

UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Conv Layer")
class ATUM_API UAtumLayerConv : public UObject, public IAtumLayerBaseConvolution
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(FAtumLayerConvOptions)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerConvOptions Options;
	
	UE_NODISCARD
	bool IsDilatedKernelGreaterThanPaddedInput(const TArray<int64>& InputSizes) const noexcept;
	
	UE_NODISCARD
	bool IsPaddingGreaterThanOrEqualToInput(const TArray<int64>& InputSizes) const noexcept;
	
	UE_NODISCARD
	bool DoesPaddingCauseMultipleWrappings(const TArray<int64>& InputSizes) const noexcept;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = true) override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 1D Layer")
class ATUM_API UAtumLayerConv1D : public UAtumLayerConv
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::Conv1d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerConv1D() noexcept;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 2D Layer")
class ATUM_API UAtumLayerConv2D : public UAtumLayerConv
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::Conv2d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerConv2D() noexcept;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 3D Layer")
class ATUM_API UAtumLayerConv3D : public UAtumLayerConv
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::Conv3d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerConv3D() noexcept;
};

#undef LOCTEXT_NAMESPACE
