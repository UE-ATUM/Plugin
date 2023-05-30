// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvTransposeOptions.h"
#include "IAtumLayerBaseConvolution.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/conv.h>
TORCH_INCLUDES_END

#include "AtumLayerConvTranspose.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerConvTranspose"

UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose Layer")
class ATUM_API UAtumLayerConvTranspose : public UObject, public IAtumLayerBaseConvolution
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(FAtumLayerConvTransposeOptions)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerConvTransposeOptions Options;
	
	UE_NODISCARD
	bool IsCalculatedOutputTensorSizeValid(const TArray<int64>& InputSizes) const noexcept;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = true) override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 1D Layer")
class ATUM_API UAtumLayerConvTranspose1D : public UAtumLayerConvTranspose
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::ConvTranspose1d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose1D() noexcept;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 2D Layer")
class ATUM_API UAtumLayerConvTranspose2D : public UAtumLayerConvTranspose
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::ConvTranspose2d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose2D() noexcept;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 3D Layer")
class ATUM_API UAtumLayerConvTranspose3D : public UAtumLayerConvTranspose
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::ConvTranspose3d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose3D() noexcept;
};

#undef LOCTEXT_NAMESPACE
