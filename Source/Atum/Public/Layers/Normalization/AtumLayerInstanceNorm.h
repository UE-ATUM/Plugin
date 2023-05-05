// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerInstanceNormOptions.h"
#include "IAtumLayerBaseNorm.h"

#include "AtumLayerInstanceNorm.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm Layer")
class ATUM_API UAtumLayerInstanceNorm : public UObject, public IAtumLayerBaseNorm
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerInstanceNormOptions Options;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerInstanceNormOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerInstanceNormOptions& GetOptions() noexcept { return Options; }
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm 1D Layer")
class ATUM_API UAtumLayerInstanceNorm1D : public UAtumLayerInstanceNorm,
public TAtumLayer<torch::nn::InstanceNorm1dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerInstanceNorm1D() noexcept;

protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm 2D Layer")
class ATUM_API UAtumLayerInstanceNorm2D : public UAtumLayerInstanceNorm,
public TAtumLayer<torch::nn::InstanceNorm2dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerInstanceNorm2D() noexcept;

protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Instance Norm 3D Layer")
class ATUM_API UAtumLayerInstanceNorm3D : public UAtumLayerInstanceNorm,
public TAtumLayer<torch::nn::InstanceNorm3dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerInstanceNorm3D() noexcept;

protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};
