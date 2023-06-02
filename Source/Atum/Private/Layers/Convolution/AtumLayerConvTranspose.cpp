// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConvTranspose.h"

#include "FunctionLibraries/AtumLibraryUtilities.h"
#include "Macros/AtumMacrosLog.h"
#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerConvTranspose"

bool UAtumLayerConvTranspose::IsCalculatedOutputTensorSizeValid(const TArray<int64>& InputSizes) const noexcept
{
	const uint64 SizeDifference = InputSizes.Num() - DimensionCount;
	const TArray<int64>& KernelSize = Options.KernelSize;
	const TArray<int64>& Stride = Options.Stride;
	const TArray<int64>& Padding = Options.Padding;
	const TArray<int64>& OutputPadding = Options.OutputPadding;
	const TArray<int64>& Dilation = Options.Dilation;
	
	bool bHasNonPositive = false;
	std::vector<int64> OutputSizes(DimensionCount);
	
	for (uint64 Index = 0ULL; Index < DimensionCount; ++Index)
	{
		OutputSizes[Index] = (InputSizes[SizeDifference + Index] - 1LL) * Stride[Index]
		- 2LL * Padding[Index] + Dilation[Index] * (KernelSize[Index] - 1LL) + OutputPadding[Index] + 1LL;
		
		bHasNonPositive |= OutputSizes[Index] < 0LL;
	}
	if (!bHasNonPositive)
		return false;
	
	ATUM_LOG(
		Error,
		TEXT("Calculated output tensor of size (%hs) is invalid!"),
		UAtumLibraryUtilities::FormatWithConjunction(OutputSizes, " x ").c_str()
	)
	return true;
}

bool UAtumLayerConvTranspose::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	bool bSuccess = AreChannelsDivisibleByGroups(Options.InChannels, Options.OutChannels, Options.Groups);
	bSuccess &= AreSizesPositive(Options.KernelSize, TEXT("Kernel Size"));
	bSuccess &= AreSizesPositive(Options.Stride, TEXT("Stride"));
	bSuccess &= AreSizesPositive(Options.Padding, TEXT("Padding"), true);
	bSuccess &= AreSizesPositive(Options.OutputPadding, TEXT("Output Padding"), true);
	bSuccess &= AreSizesPositive(Options.Dilation, TEXT("Dilation"));
	return bSuccess;
}

bool UAtumLayerConvTranspose::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	[[maybe_unused]] TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	
	bool bSuccess = AreInputSizesValid(InputSizes, Options.InChannels);
	bSuccess &= !IsCalculatedOutputTensorSizeValid(InputSizes);
	return bSuccess;
}

bool UAtumLayerConvTranspose::LoadFromFile_Implementation(const FString& RelativePath)
{
	return IAtumLayer::LoadFromFile_Implementation(RelativePath);
}

UAtumLayerConvTranspose1D::UAtumLayerConvTranspose1D() noexcept
{
	DimensionCount = 1ULL;
	ValidInputSizes.push_back(2LL);
	ValidInputSizes.push_back(3LL);
	Options = FAtumLayerConvTransposeOptions(DimensionCount);
}

bool UAtumLayerConvTranspose1D::OnInitializeData_Implementation(const bool bRetry)
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module = MakeShared<torch::nn::ConvTranspose1d>(std::make_shared<torch::nn::ConvTranspose1dImpl>(
		static_cast<torch::nn::ConvTranspose1dOptions>(Options)
	));
	return true;
}

bool UAtumLayerConvTranspose1D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

bool UAtumLayerConvTranspose1D::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!Super::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

UAtumLayerConvTranspose2D::UAtumLayerConvTranspose2D() noexcept
{
	DimensionCount = 2ULL;
	ValidInputSizes.push_back(3LL);
	ValidInputSizes.push_back(4LL);
	Options = FAtumLayerConvTransposeOptions(DimensionCount);
}

bool UAtumLayerConvTranspose2D::OnInitializeData_Implementation(const bool bRetry)
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module = MakeShared<torch::nn::ConvTranspose2d>(std::make_shared<torch::nn::ConvTranspose2dImpl>(
		static_cast<torch::nn::ConvTranspose2dOptions>(Options)
	));
	return true;
}

bool UAtumLayerConvTranspose2D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

bool UAtumLayerConvTranspose2D::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!Super::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

UAtumLayerConvTranspose3D::UAtumLayerConvTranspose3D() noexcept
{
	DimensionCount = 3ULL;
	ValidInputSizes.push_back(4LL);
	ValidInputSizes.push_back(5LL);
	Options = FAtumLayerConvTransposeOptions(DimensionCount);
}

bool UAtumLayerConvTranspose3D::OnInitializeData_Implementation(const bool bRetry)
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module = MakeShared<torch::nn::ConvTranspose3d>(std::make_shared<torch::nn::ConvTranspose3dImpl>(
		static_cast<torch::nn::ConvTranspose3dOptions>(Options)
	));
	return true;
}

bool UAtumLayerConvTranspose3D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

bool UAtumLayerConvTranspose3D::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!Super::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

#undef LOCTEXT_NAMESPACE
