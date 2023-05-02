// © 2023 Kaya Adrian.

#include "Layers/AtumLayerBatchNorm.h"

#include "IAtum.h"


FAtumOptionsBatchNorm::FAtumOptionsBatchNorm() noexcept :
NumFeatures(1),
Epsilon(1e-5),
Momentum(0.1),
bAffine(true),
bTrackRunningStats(true)
{
}

FAtumOptionsBatchNorm::operator torch::nn::BatchNormOptions() const noexcept
{
	return torch::nn::BatchNormOptions(NumFeatures)
	.eps(Epsilon)
	.momentum(Momentum == 0.0 ? c10::nullopt : c10::optional<double>(Momentum))
	.affine(bAffine)
	.track_running_stats(bTrackRunningStats);
}

bool UAtumLayerBatchNorm1D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::BatchNorm1dImpl(static_cast<torch::nn::BatchNormOptions>(GetOptions())));
	return true;
}

bool UAtumLayerBatchNorm1D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	if (const int32 SizeCount = InputSizes.Num(); SizeCount != 2 && SizeCount != 3)
	{
		UE_LOG(LogAtum, Error, TEXT("BatchNorm1D - Expected 2D or 3D input but got %dD!"), SizeCount)
		return false;
	}

	const int64 GivenFeatures = InputSizes[1];
	if (const int64 ExpectedFeatures = Module->options.num_features(); GivenFeatures != ExpectedFeatures)
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("BatchNorm1D - Expected %lld features but got %lld!"),
			ExpectedFeatures,
			GivenFeatures
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}

bool UAtumLayerBatchNorm2D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::BatchNorm2dImpl(static_cast<torch::nn::BatchNormOptions>(GetOptions())));
	return true;
}

bool UAtumLayerBatchNorm2D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	if (const int32 SizeCount = InputSizes.Num(); SizeCount != 4)
	{
		UE_LOG(LogAtum, Error, TEXT("BatchNorm2D - Expected 4D input but got %dD!"), SizeCount)
		return false;
	}

	const int64 GivenFeatures = InputSizes[1];
	if (const int64 ExpectedFeatures = Module->options.num_features(); GivenFeatures != ExpectedFeatures)
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("BatchNorm2D - Expected %lld features but got %lld!"),
			ExpectedFeatures,
			GivenFeatures
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}

bool UAtumLayerBatchNorm3D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::BatchNorm3dImpl(static_cast<torch::nn::BatchNormOptions>(GetOptions())));
	return true;
}

bool UAtumLayerBatchNorm3D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	if (const int32 SizeCount = InputSizes.Num(); SizeCount != 5)
	{
		UE_LOG(LogAtum, Error, TEXT("BatchNorm3D - Expected 5D input but got %dD!"), SizeCount)
		return false;
	}

	const int64 GivenFeatures = InputSizes[1];
	if (const int64 ExpectedFeatures = Module->options.num_features(); GivenFeatures != ExpectedFeatures)
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("BatchNorm3D - Expected %lld features but got %lld!"),
			ExpectedFeatures,
			GivenFeatures
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}
