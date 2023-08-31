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

/**
 * Base Batch Normalisation layer implementation
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm Layer")
class ATUM_API UAtumLayerBatchNorm : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(FAtumLayerBatchNormOptions)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerBatchNormOptions Options;
	
	/**
	 * Function that runs when IAtumLayer::Forward is called
	 * 
	 * @param Input Tensor to operate on
	 * @param Output The resulting tensor
	 * @return Did the layer forward successfully?
	 */
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


/**
 * 1D Batch Normalisation layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 1D Layer")
class ATUM_API UAtumLayerBatchNorm1D : public UAtumLayerBatchNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::BatchNorm1d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerBatchNorm1D() noexcept;
	
protected:
	/**
	 * Loads the layer data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
};


/**
 * 2D Batch Normalisation layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 2D Layer")
class ATUM_API UAtumLayerBatchNorm2D : public UAtumLayerBatchNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::BatchNorm2d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerBatchNorm2D() noexcept;
	
protected:
	/**
	 * Loads the layer data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
};


/**
 * 3D Batch Normalisation layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 3D Layer")
class ATUM_API UAtumLayerBatchNorm3D : public UAtumLayerBatchNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::BatchNorm3d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerBatchNorm3D() noexcept;
	
protected:
	/**
	 * Loads the layer data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
};

#undef LOCTEXT_NAMESPACE
