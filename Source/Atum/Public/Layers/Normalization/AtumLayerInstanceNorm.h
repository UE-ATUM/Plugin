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

/**
 * Base Instance Normalisation layer implementation
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm Layer")
class ATUM_API UAtumLayerInstanceNorm : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(FAtumLayerInstanceNormOptions)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerInstanceNormOptions Options;
	
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
 * 1D Instance Normalisation layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm 1D Layer")
class ATUM_API UAtumLayerInstanceNorm1D : public UAtumLayerInstanceNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::InstanceNorm1d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerInstanceNorm1D() noexcept;
	
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
 * 2D Instance Normalisation layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm 2D Layer")
class ATUM_API UAtumLayerInstanceNorm2D : public UAtumLayerInstanceNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::InstanceNorm2d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerInstanceNorm2D() noexcept;
	
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
 * 3D Instance Normalisation layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm 3D Layer")
class ATUM_API UAtumLayerInstanceNorm3D : public UAtumLayerInstanceNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::InstanceNorm3d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerInstanceNorm3D() noexcept;
	
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
