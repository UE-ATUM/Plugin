// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvTransposeOptions.h"
#include "IAtumLayerBaseConv.h"

#include "AtumLayerConvTranspose.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose Layer")
class ATUM_API UAtumLayerConvTranspose : public UObject, public IAtumLayerBaseConv
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerConvTransposeOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerConvTransposeOptions& GetOptions() const noexcept { return Options; }

	UE_NODISCARD
	FORCEINLINE FAtumLayerConvTransposeOptions& GetOptions() noexcept { return Options; }
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 1D Layer")
class ATUM_API UAtumLayerConvTranspose1D : public UAtumLayerConvTranspose,
public TAtumLayer<torch::nn::ConvTranspose1dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose1D() noexcept;
	
protected:
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

public:
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose2D() noexcept;
	
protected:
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

public:
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose3D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};
