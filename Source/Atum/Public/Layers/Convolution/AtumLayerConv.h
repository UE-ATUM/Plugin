// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvOptions.h"
#include "IAtumLayerBaseConv.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/conv.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerConv.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Conv Layer")
class ATUM_API UAtumLayerConv : public UObject, public IAtumLayerBaseConv
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerConvOptions Options;
	
	UE_NODISCARD
	bool IsDilatedKernelGreaterThanPaddedInput(const TArray<int64>& InputSizes) const noexcept;

	UE_NODISCARD
	bool IsPaddingGreaterThanOrEqualToInput(const TArray<int64>& InputSizes) const noexcept;

	UE_NODISCARD
	bool DoesPaddingCauseMultipleWrappings(const TArray<int64>& InputSizes) const noexcept;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerConvOptions& GetOptions() const noexcept { return Options; }

	UE_NODISCARD
	FORCEINLINE FAtumLayerConvOptions& GetOptions() noexcept { return Options; }
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 1D Layer")
class ATUM_API UAtumLayerConv1D : public UAtumLayerConv, public TAtumLayer<torch::nn::Conv1dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerConv1D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 2D Layer")
class ATUM_API UAtumLayerConv2D : public UAtumLayerConv, public TAtumLayer<torch::nn::Conv2dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerConv2D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 3D Layer")
class ATUM_API UAtumLayerConv3D : public UAtumLayerConv, public TAtumLayer<torch::nn::Conv3dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerConv3D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};
