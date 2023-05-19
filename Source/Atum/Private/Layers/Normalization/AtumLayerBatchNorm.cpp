// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerBatchNorm.h"

#include "Tensors/IAtumTensor.h"


bool UAtumLayerBatchNorm::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	[[maybe_unused]] TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	return AreInputSizesValid(InputSizes, Options.NumFeatures);
}

UAtumLayerBatchNorm1D::UAtumLayerBatchNorm1D() noexcept
{
	DimensionCount = 1u;
	ValidInputSizes.push_back(2);
	ValidInputSizes.push_back(3);
}

bool UAtumLayerBatchNorm1D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::BatchNorm1d(std::make_shared<torch::nn::BatchNorm1dImpl>(
		static_cast<torch::nn::BatchNormOptions>(Options)
	)));
	return true;
}

bool UAtumLayerBatchNorm1D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}

UAtumLayerBatchNorm2D::UAtumLayerBatchNorm2D() noexcept
{
	DimensionCount = 2u;
	ValidInputSizes.push_back(4);
}

bool UAtumLayerBatchNorm2D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::BatchNorm2d(std::make_shared<torch::nn::BatchNorm2dImpl>(
		static_cast<torch::nn::BatchNormOptions>(Options)
	)));
	return true;
}

bool UAtumLayerBatchNorm2D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}

UAtumLayerBatchNorm3D::UAtumLayerBatchNorm3D() noexcept
{
	DimensionCount = 3u;
	ValidInputSizes.push_back(5);
}

bool UAtumLayerBatchNorm3D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::BatchNorm3d(std::make_shared<torch::nn::BatchNorm3dImpl>(
		static_cast<torch::nn::BatchNormOptions>(Options)
	)));
	return true;
}

bool UAtumLayerBatchNorm3D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}
