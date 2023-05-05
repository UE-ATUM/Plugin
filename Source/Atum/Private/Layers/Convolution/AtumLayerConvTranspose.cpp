// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConvTranspose.h"


bool UAtumLayerConvTranspose::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	const int64 Groups = Options.Groups;
	if (Groups <= 0)
	{
		UE_LOG(LogAtum, Error, TEXT("There must exist at least 1 group!"))
		return false;
	}
	if (Options.InChannels % Groups != 0 || Options.OutChannels % Groups != 0)
	{
		UE_LOG(LogAtum, Error, TEXT("Input and output channels must both be divisible by the group count!"))
		return false;
	}
	
	const TArray<int64>& KernelSize = Options.KernelSize;
	const TArray<int64>& Stride = Options.Stride;
	const TArray<int64>& Padding = Options.Padding;
	const TArray<int64>& OutputPadding = Options.OutputPadding;
	const TArray<int64>& Dilation = Options.Dilation;
	
	for (uint64 Index = 0u; Index < DimensionCount; ++Index)
	{
		if (KernelSize[Index] <= 0)
		{
			UE_LOG(LogAtum, Error, TEXT("Kernel size must be composed of positive integers!"))
			return false;
		}
		if (Stride[Index] <= 0)
		{
			UE_LOG(LogAtum, Error, TEXT("Stride must be composed of positive integers!"))
			return false;
		}
		if (Padding[Index] < 0)
		{
			UE_LOG(LogAtum, Error, TEXT("Padding cannot be composed of negative integers!"))
			return false;
		}
		if (OutputPadding[Index] < 0)
		{
			UE_LOG(LogAtum, Error, TEXT("Output padding cannot be composed of negative integers!"))
			return false;
		}
		if (Dilation[Index] <= 0)
		{
			UE_LOG(LogAtum, Error, TEXT("Dilation must be composed of positive integers!"))
			return false;
		}
	}

	return true;
}

bool UAtumLayerConvTranspose::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	const int32 SizeCount = InputSizes.Num();
	const int32 SizeDifference = SizeCount - DimensionCount;

	if (!AreInputSizesValid(SizeCount, InputSizes[SizeDifference - 1], Options.InChannels))
		return false;

	const TArray<int64>& KernelSize = Options.KernelSize;
	const TArray<int64>& Stride = Options.Stride;
	const TArray<int64>& Padding = Options.Padding;
	const TArray<int64>& OutputPadding = Options.OutputPadding;
	const TArray<int64>& Dilation = Options.Dilation;

	std::vector<int64> OutputSizes(DimensionCount);
	bool bOutputHasNegativeSize = false;
	
	for (uint64 Index = 0u; Index < DimensionCount; ++Index)
	{
		OutputSizes[Index] = (InputSizes[SizeDifference + Index] - 1) * Stride[Index]
		- 2 * Padding[Index] + Dilation[Index] * (KernelSize[Index] - 1) + OutputPadding[Index] + 1;
		
		bOutputHasNegativeSize |= OutputSizes[Index] < 0;
	}
	if (bOutputHasNegativeSize)
	{
		std::ostringstream OutputSizesStream;
		std::copy(
			OutputSizes.begin(),
			std::prev(OutputSizes.end()),
			std::ostream_iterator<int64>(OutputSizesStream, " x ")
		);
		OutputSizesStream << OutputSizes.back();
		
		UE_LOG(
			LogAtum,
			Error,
			TEXT("Calculated output tensor of size (%hs) is invalid!"),
			OutputSizesStream.str().c_str()
		)
		return false;
	}

	return true;
}

UAtumLayerConvTranspose1D::UAtumLayerConvTranspose1D() noexcept
{
	DimensionCount = 1u;
}

bool UAtumLayerConvTranspose1D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module.Reset(new torch::nn::ConvTranspose1dImpl(static_cast<torch::nn::ConvTranspose1dOptions>(Options)));
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
}

bool UAtumLayerConvTranspose2D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module.Reset(new torch::nn::ConvTranspose2dImpl(static_cast<torch::nn::ConvTranspose2dOptions>(Options)));
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
}

bool UAtumLayerConvTranspose3D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module.Reset(new torch::nn::ConvTranspose3dImpl(static_cast<torch::nn::ConvTranspose3dOptions>(Options)));
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
