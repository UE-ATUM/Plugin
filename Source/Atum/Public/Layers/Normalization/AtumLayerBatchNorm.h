// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerBatchNormOptions.h"
#include "IAtumLayerBaseNormalization.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/batchnorm.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerBatchNorm.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm Layer")
class ATUM_API UAtumLayerBatchNorm : public UObject, public IAtumLayerBaseNormalization
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerBatchNormOptions Options;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerBatchNormOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerBatchNormOptions& GetOptions() noexcept { return Options; }
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 1D Layer")
class ATUM_API UAtumLayerBatchNorm1D : public UAtumLayerBatchNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::BatchNorm1d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerBatchNorm1D() noexcept;

protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 2D Layer")
class ATUM_API UAtumLayerBatchNorm2D : public UAtumLayerBatchNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::BatchNorm2d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerBatchNorm2D() noexcept;

protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 3D Layer")
class ATUM_API UAtumLayerBatchNorm3D : public UAtumLayerBatchNorm
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::BatchNorm3d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerBatchNorm3D() noexcept;

protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};
