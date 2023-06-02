// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerBatchNormOptions.h"
#include "IAtumLayerBaseNormalization.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/batchnorm.h>
TORCH_INCLUDES_END

#include "AtumLayerBatchNorm.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerBatchNorm"

UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm Layer")
class ATUM_API UAtumLayerBatchNorm : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(FAtumLayerBatchNormOptions)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerBatchNormOptions Options;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 1D Layer")
class ATUM_API UAtumLayerBatchNorm1D : public UAtumLayerBatchNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::BatchNorm1d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerBatchNorm1D() noexcept;
	
protected:
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 2D Layer")
class ATUM_API UAtumLayerBatchNorm2D : public UAtumLayerBatchNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::BatchNorm2d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerBatchNorm2D() noexcept;
	
protected:
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 3D Layer")
class ATUM_API UAtumLayerBatchNorm3D : public UAtumLayerBatchNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::BatchNorm3d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerBatchNorm3D() noexcept;
	
protected:
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
};

#undef LOCTEXT_NAMESPACE
