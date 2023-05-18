// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerInstanceNorm.h"


bool UAtumLayerInstanceNorm::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	[[maybe_unused]] TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	return AreInputSizesValid(InputSizes, Options.NumFeatures);
}

UAtumLayerInstanceNorm1D::UAtumLayerInstanceNorm1D() noexcept
{
	DimensionCount = 1u;
	ValidInputSizes.push_back(2);
	ValidInputSizes.push_back(3);
}

bool UAtumLayerInstanceNorm1D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module = std::make_shared<torch::nn::InstanceNorm1dImpl>(static_cast<torch::nn::InstanceNormOptions>(Options));
	return true;
}

bool UAtumLayerInstanceNorm1D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kDouble)));
	return true;
}

UAtumLayerInstanceNorm2D::UAtumLayerInstanceNorm2D() noexcept
{
	DimensionCount = 2u;
	ValidInputSizes.push_back(3);
	ValidInputSizes.push_back(4);
}

bool UAtumLayerInstanceNorm2D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module = std::make_shared<torch::nn::InstanceNorm2dImpl>(static_cast<torch::nn::InstanceNormOptions>(Options));
	return true;
}

bool UAtumLayerInstanceNorm2D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kDouble)));
	return true;
}

UAtumLayerInstanceNorm3D::UAtumLayerInstanceNorm3D() noexcept
{
	DimensionCount = 3u;
	ValidInputSizes.push_back(4);
	ValidInputSizes.push_back(5);
}

bool UAtumLayerInstanceNorm3D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module = std::make_shared<torch::nn::InstanceNorm3dImpl>(static_cast<torch::nn::InstanceNormOptions>(Options));
	return true;
}

bool UAtumLayerInstanceNorm3D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kDouble)));
	return true;
}
