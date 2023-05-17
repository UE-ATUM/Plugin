// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConv.h"

#include "FunctionLibraries/AtumLibraryUtilities.h"


bool UAtumLayerConv::IsDilatedKernelGreaterThanPaddedInput(const TArray<int64>& InputSizes) const noexcept
{
	const uint64 SizeDifference = InputSizes.Num() - DimensionCount;
	const TArray<int64>& KernelSize = Options.KernelSize;
	const TArray<int64>& Padding = Options.Padding;
	const TArray<int64>& Dilation = Options.Dilation;
	
	bool bIsBigger = false;
	std::vector<int64> PaddedInput(DimensionCount);
	std::vector<int64> DilatedKernel(DimensionCount);
	
	for (uint64 Index = 0u; Index < DimensionCount; ++Index)
	{
		PaddedInput[Index] = InputSizes[SizeDifference + Index] + 2 * Padding[Index];
		DilatedKernel[Index] = Dilation[Index] * (KernelSize[Index] - 1) + 1;
		
		bIsBigger |= PaddedInput[Index] < DilatedKernel[Index];
	}
	if (!bIsBigger)
		return false;
	
	UE_LOG(
		LogAtum,
		Error,
		TEXT("Dilated kernel (%hs) has at least one dimension greater than the padded input (%hs)!"),
		UAtumLibraryUtilities::FormatWithConjunction(DilatedKernel, " x ").c_str(),
		UAtumLibraryUtilities::FormatWithConjunction(PaddedInput, " x ").c_str()
	)
	return true;
}

bool UAtumLayerConv::IsPaddingGreaterThanOrEqualToInput(const TArray<int64>& InputSizes) const noexcept
{
	if (Options.PaddingMode != EAtumConvPaddingMode::Reflect)
		return false;
	
	const uint64 SizeDifference = InputSizes.Num() - DimensionCount;
	const TArray<int64>& Padding = Options.Padding;
	
	bool bIsBigger = false;
	std::vector<int64> UnpaddedInput(DimensionCount);
	std::vector<int64> PaddingVector(DimensionCount);
	
	for (uint64 Index = 0u; Index < DimensionCount; ++Index)
	{
		UnpaddedInput[Index] = InputSizes[SizeDifference + Index];
		PaddingVector[Index] = Padding[Index];
		
		bIsBigger |= UnpaddedInput[Index] <= PaddingVector[Index];
	}
	if (!bIsBigger)
		return false;
	
	UE_LOG(
		LogAtum,
		Error,
		TEXT("Padding (%hs) has at least one dimension greater than or equal to the input (%hs)!"),
		UAtumLibraryUtilities::FormatWithConjunction(PaddingVector, " x ").c_str(),
		UAtumLibraryUtilities::FormatWithConjunction(UnpaddedInput, " x ").c_str()
	)
	return true;
}

bool UAtumLayerConv::DoesPaddingCauseMultipleWrappings(const TArray<int64>& InputSizes) const noexcept
{
	if (Options.PaddingMode != EAtumConvPaddingMode::Circular)
		return false;
	
	const uint64 SizeDifference = InputSizes.Num() - DimensionCount;
	const TArray<int64>& Padding = Options.Padding;
	
	bool bMultipleWrappings = false;
	std::vector<int64> UnpaddedInput(DimensionCount);
	std::vector<int64> PaddingVector(DimensionCount);
	
	for (uint64 Index = 0u; Index < DimensionCount; ++Index)
	{
		UnpaddedInput[Index] = InputSizes[SizeDifference + Index];
		PaddingVector[Index] = Padding[Index];
		
		bMultipleWrappings |= UnpaddedInput[Index] < PaddingVector[Index];
	}
	if (!bMultipleWrappings)
		return false;
	
	UE_LOG(
		LogAtum,
		Error,
		TEXT("Padding (%hs) has at least one dimension greater than the input (%hs)!"),
		UAtumLibraryUtilities::FormatWithConjunction(PaddingVector, " x ").c_str(),
		UAtumLibraryUtilities::FormatWithConjunction(UnpaddedInput, " x ").c_str()
	)
	return true;
}

bool UAtumLayerConv::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	bool bSuccess = AreChannelsDivisibleByGroups(Options.InChannels, Options.OutChannels, Options.Groups);
	bSuccess &= AreSizesPositive(Options.KernelSize, TEXT("Kernel Size"));
	bSuccess &= AreSizesPositive(Options.Stride, TEXT("Stride"));
	bSuccess &= AreSizesPositive(Options.Padding, TEXT("Padding"), true);
	bSuccess &= AreSizesPositive(Options.Dilation, TEXT("Dilation"));
	return bSuccess;
}

bool UAtumLayerConv::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	[[maybe_unused]] TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	
	bool bSuccess = AreInputSizesValid(InputSizes, Options.InChannels);
	bSuccess &= !IsDilatedKernelGreaterThanPaddedInput(InputSizes);
	bSuccess &= !IsPaddingGreaterThanOrEqualToInput(InputSizes);
	bSuccess &= !DoesPaddingCauseMultipleWrappings(InputSizes);
	return bSuccess;
}

UAtumLayerConv1D::UAtumLayerConv1D() noexcept
{
	DimensionCount = 1u;
	ValidInputSizes.push_back(2);
	ValidInputSizes.push_back(3);
}

bool UAtumLayerConv1D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module->options = static_cast<torch::nn::detail::ConvNdOptions<1>>(Options);
	return true;
}

bool UAtumLayerConv1D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

UAtumLayerConv2D::UAtumLayerConv2D() noexcept
{
	DimensionCount = 2u;
	ValidInputSizes.push_back(3);
	ValidInputSizes.push_back(4);
}

bool UAtumLayerConv2D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module->options = static_cast<torch::nn::detail::ConvNdOptions<2>>(Options);
	return true;
}

bool UAtumLayerConv2D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

UAtumLayerConv3D::UAtumLayerConv3D() noexcept
{
	DimensionCount = 3u;
	ValidInputSizes.push_back(4);
	ValidInputSizes.push_back(5);
}

bool UAtumLayerConv3D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;

	Module->options = static_cast<torch::nn::detail::ConvNdOptions<3>>(Options);
	return true;
}

bool UAtumLayerConv3D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	if (!Super::OnForward_Implementation(Input, Output))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}
