// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerBatchNorm.h"

#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerBatchNorm"

bool UAtumLayerBatchNorm::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	[[maybe_unused]] TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	return AreInputSizesValid(InputSizes, Options.NumFeatures);
}

bool UAtumLayerBatchNorm::LoadFromFile_Implementation(const FString& RelativePath)
{
	return IAtumLayer::LoadFromFile_Implementation(RelativePath);
}

UAtumLayerBatchNorm1D::UAtumLayerBatchNorm1D() noexcept
{
	DimensionCount = 1ULL;
	ValidInputSizes.push_back(2LL);
	ValidInputSizes.push_back(3LL);
}

bool UAtumLayerBatchNorm1D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShared<torch::nn::BatchNorm1d>(std::make_shared<torch::nn::BatchNorm1dImpl>(
		static_cast<torch::nn::BatchNormOptions>(Options)
	));
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

bool UAtumLayerBatchNorm1D::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!IAtumLayer::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

UAtumLayerBatchNorm2D::UAtumLayerBatchNorm2D() noexcept
{
	DimensionCount = 2ULL;
	ValidInputSizes.push_back(4LL);
}

bool UAtumLayerBatchNorm2D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShared<torch::nn::BatchNorm2d>(std::make_shared<torch::nn::BatchNorm2dImpl>(
		static_cast<torch::nn::BatchNormOptions>(Options)
	));
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

bool UAtumLayerBatchNorm2D::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!IAtumLayer::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

UAtumLayerBatchNorm3D::UAtumLayerBatchNorm3D() noexcept
{
	DimensionCount = 3ULL;
	ValidInputSizes.push_back(5LL);
}

bool UAtumLayerBatchNorm3D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShared<torch::nn::BatchNorm3d>(std::make_shared<torch::nn::BatchNorm3dImpl>(
		static_cast<torch::nn::BatchNormOptions>(Options)
	));
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

bool UAtumLayerBatchNorm3D::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!IAtumLayer::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

#undef LOCTEXT_NAMESPACE
