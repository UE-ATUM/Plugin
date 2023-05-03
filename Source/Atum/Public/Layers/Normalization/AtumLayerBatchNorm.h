// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

#include "AtumLayerBatchNorm.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Batch Norm Options")
struct ATUM_API FAtumOptionsBatchNorm
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 NumFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Epsilon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	double Momentum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bAffine;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bTrackRunningStats;

	UE_NODISCARD_CTOR
	FAtumOptionsBatchNorm() noexcept;
	
	UE_NODISCARD
	explicit operator torch::nn::BatchNormOptions() const noexcept;
};


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm Layer")
class ATUM_API UAtumLayerBatchNorm : public UObject, public IAtumLayer
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumOptionsBatchNorm Options;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumOptionsBatchNorm& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumOptionsBatchNorm& GetOptions() noexcept { return Options; }
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 1D Layer")
class ATUM_API UAtumLayerBatchNorm1D : public UAtumLayerBatchNorm, public TAtumLayer<torch::nn::BatchNorm1dImpl>
{
	GENERATED_BODY()

protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 2D Layer")
class ATUM_API UAtumLayerBatchNorm2D : public UAtumLayerBatchNorm, public TAtumLayer<torch::nn::BatchNorm2dImpl>
{
	GENERATED_BODY()

protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 3D Layer")
class ATUM_API UAtumLayerBatchNorm3D : public UAtumLayerBatchNorm, public TAtumLayer<torch::nn::BatchNorm3dImpl>
{
	GENERATED_BODY()

protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};
