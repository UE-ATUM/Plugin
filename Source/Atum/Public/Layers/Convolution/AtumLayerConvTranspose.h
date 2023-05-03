// © 2023 Kaya Adrian.

#pragma once

#include "AtumOptionsConvTranspose.h"
#include "Layers/IAtumLayer.h"

#include "AtumLayerConvTranspose.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose Layer")
class ATUM_API UAtumLayerConvTranspose : public UObject, public IAtumLayer
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumOptionsConvTranspose Options;

public:
	FORCEINLINE int64 FindOutputDimension(const int64 InputDimension, const int32 Index) const noexcept
	{
		return (InputDimension - 1) * Options.Stride[Index] - 2 * Options.Padding[Index]
		+ Options.Dilation[Index] * (Options.KernelSize[Index] - 1) + Options.OutputPadding[Index] + 1;
	}

protected:
	virtual CONSTEXPR uint64 GetDimensionCount() const noexcept;

	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumOptionsConvTranspose& GetOptions() const noexcept { return Options; }

	UE_NODISCARD
	FORCEINLINE FAtumOptionsConvTranspose& GetOptions() noexcept { return Options; }
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 1D Layer")
class ATUM_API UAtumLayerConvTranspose1D : public UAtumLayerConvTranspose,
public TAtumLayer<torch::nn::ConvTranspose1dImpl>
{
	GENERATED_BODY()
	
protected:
	virtual CONSTEXPR uint64 GetDimensionCount() const noexcept override;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 2D Layer")
class ATUM_API UAtumLayerConvTranspose2D : public UAtumLayerConvTranspose,
public TAtumLayer<torch::nn::ConvTranspose2dImpl>
{
	GENERATED_BODY()
	
protected:
	virtual CONSTEXPR uint64 GetDimensionCount() const noexcept override;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 3D Layer")
class ATUM_API UAtumLayerConvTranspose3D : public UAtumLayerConvTranspose,
public TAtumLayer<torch::nn::ConvTranspose3dImpl>
{
	GENERATED_BODY()
	
protected:
	virtual CONSTEXPR uint64 GetDimensionCount() const noexcept override;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};
