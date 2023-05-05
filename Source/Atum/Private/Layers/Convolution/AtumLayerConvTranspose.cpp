// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConvTranspose.h"

#include "IAtum.h"


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
	
	for (uint64 Index = 0u; Index < DimensionCount; ++Index)
	{
		OutputSizes[Index] = (InputSizes[SizeDifference + Index] - 1) * Stride[Index]
		- 2 * Padding[Index] + Dilation[Index] * (KernelSize[Index] - 1) + OutputPadding[Index] + 1;
		
		bHasNonPositive |= OutputSizes[Index] < 0;
	}
	if (!bHasNonPositive)
		return false;

	std::ostringstream OutputSizesStream;
	std::copy(
		OutputSizes.begin(),
		std::prev(OutputSizes.end()),
		std::ostream_iterator<int64>(OutputSizesStream, " x ")
	);
	OutputSizesStream << OutputSizes.back();
		
	UE_LOG(LogAtum, Error, TEXT("Calculated output tensor of size (%hs) is invalid!"), OutputSizesStream.str().c_str())
	return true;
}

bool UAtumLayerConvTranspose::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	bool bValidData = AreChannelsDivisibleByGroups(Options.InChannels, Options.OutChannels, Options.Groups);
	bValidData &= AreSizesPositive(Options.KernelSize, TEXT("Kernel Size"));
	bValidData &= AreSizesPositive(Options.Stride, TEXT("Stride"));
	bValidData &= AreSizesPositive(Options.Padding, TEXT("Padding"), true);
	bValidData &= AreSizesPositive(Options.OutputPadding, TEXT("Output Padding"), true);
	bValidData &= AreSizesPositive(Options.Dilation, TEXT("Dilation"));
	
	return bValidData;
}

bool UAtumLayerConvTranspose::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	bool bSuccess = AreInputSizesValid(InputSizes, Options.InChannels);
	bSuccess &= !IsCalculatedOutputTensorSizeValid(InputSizes);
	return bSuccess;
}

UAtumLayerConvTranspose1D::UAtumLayerConvTranspose1D() noexcept
{
	DimensionCount = 1u;
	ValidInputSizes.push_back(2);
	ValidInputSizes.push_back(3);
}

bool UAtumLayerConvTranspose1D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	MakeModule<torch::nn::ConvTranspose1dOptions>(Options);
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
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

UAtumLayerConvTranspose2D::UAtumLayerConvTranspose2D() noexcept
{
	DimensionCount = 2u;
	ValidInputSizes.push_back(3);
	ValidInputSizes.push_back(4);
}

bool UAtumLayerConvTranspose2D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	MakeModule<torch::nn::ConvTranspose2dOptions>(Options);
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
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

UAtumLayerConvTranspose3D::UAtumLayerConvTranspose3D() noexcept
{
	DimensionCount = 3u;
	ValidInputSizes.push_back(4);
	ValidInputSizes.push_back(5);
}

bool UAtumLayerConvTranspose3D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	MakeModule<torch::nn::ConvTranspose3dOptions>(Options);
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
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}
