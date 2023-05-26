// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerInstanceNorm.h"

#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerInstanceNorm"

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
	DimensionCount = 1ULL;
	ValidInputSizes.push_back(2LL);
	ValidInputSizes.push_back(3LL);
}

bool UAtumLayerInstanceNorm1D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShareable(new torch::nn::InstanceNorm1d(std::make_shared<torch::nn::InstanceNorm1dImpl>(
		static_cast<torch::nn::InstanceNormOptions>(Options)
	)));
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
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kDouble)));
	return true;
}

UAtumLayerInstanceNorm2D::UAtumLayerInstanceNorm2D() noexcept
{
	DimensionCount = 2ULL;
	ValidInputSizes.push_back(3LL);
	ValidInputSizes.push_back(4LL);
}

bool UAtumLayerInstanceNorm2D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShareable(new torch::nn::InstanceNorm2d(std::make_shared<torch::nn::InstanceNorm2dImpl>(
		static_cast<torch::nn::InstanceNormOptions>(Options)
	)));
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
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kDouble)));
	return true;
}

UAtumLayerInstanceNorm3D::UAtumLayerInstanceNorm3D() noexcept
{
	DimensionCount = 3ULL;
	ValidInputSizes.push_back(4LL);
	ValidInputSizes.push_back(5LL);
}

bool UAtumLayerInstanceNorm3D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShareable(new torch::nn::InstanceNorm3d(std::make_shared<torch::nn::InstanceNorm3dImpl>(
		static_cast<torch::nn::InstanceNormOptions>(Options)
	)));
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
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kDouble)));
	return true;
}

#undef LOCTEXT_NAMESPACE
