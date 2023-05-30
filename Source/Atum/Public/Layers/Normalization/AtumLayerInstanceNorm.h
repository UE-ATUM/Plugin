// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerInstanceNormOptions.h"
#include "IAtumLayerBaseNormalization.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/instancenorm.h>
TORCH_INCLUDES_END

#include "AtumLayerInstanceNorm.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerInstanceNorm"

UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm Layer")
class ATUM_API UAtumLayerInstanceNorm : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(FAtumLayerInstanceNormOptions)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerInstanceNormOptions Options;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm 1D Layer")
class ATUM_API UAtumLayerInstanceNorm1D : public UAtumLayerInstanceNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::InstanceNorm1d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerInstanceNorm1D() noexcept;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm 2D Layer")
class ATUM_API UAtumLayerInstanceNorm2D : public UAtumLayerInstanceNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::InstanceNorm2d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerInstanceNorm2D() noexcept;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm 3D Layer")
class ATUM_API UAtumLayerInstanceNorm3D : public UAtumLayerInstanceNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::InstanceNorm3d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerInstanceNorm3D() noexcept;
};

#undef LOCTEXT_NAMESPACE
