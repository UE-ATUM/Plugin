// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConv.h"


bool UAtumLayerBaseConv::OnInitializeData_Implementation(const bool bRetry) noexcept
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
		if (Dilation[Index] <= 0)
		{
			UE_LOG(LogAtum, Error, TEXT("Dilation must be composed of positive integers!"))
			return false;
		}
	}
	
	return true;
}

bool UAtumLayerBaseConv::OnForward_Implementation(
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
	const TArray<int64>& Padding = Options.Padding;
	const TArray<int64>& Dilation = Options.Dilation;

	std::vector<int64> PaddedInput(DimensionCount);
	std::vector<int64> DilatedKernel(DimensionCount);
	bool bDilatedKernelTooBig = false;
	
	for (uint64 Index = 0u; Index < DimensionCount; ++Index)
	{
		PaddedInput[Index] = InputSizes[SizeDifference + Index] + 2 * Padding[Index];
		DilatedKernel[Index] = Dilation[Index] * (KernelSize[Index] - 1) + 1;
		bDilatedKernelTooBig |= PaddedInput[Index] < DilatedKernel[Index];
	}
	if (bDilatedKernelTooBig)
	{
		std::ostringstream PaddedInputStream;
		std::copy(
			PaddedInput.begin(),
			std::prev(PaddedInput.end()),
			std::ostream_iterator<int64>(PaddedInputStream, " x ")
		);
		PaddedInputStream << PaddedInput.back();

		std::ostringstream DilatedKernelStream;
		std::copy(
			DilatedKernel.begin(),
			std::prev(DilatedKernel.end()),
			std::ostream_iterator<int64>(DilatedKernelStream, " x ")
		);
		DilatedKernelStream << DilatedKernel.back();
		
		UE_LOG(
			LogAtum,
			Error,
			TEXT("Dilated kernel size (%hs) has at least one channel bigger than the padded input (%hs)!"),
			DilatedKernelStream.str().c_str(),
			PaddedInputStream.str().c_str()
		)
		return false;
	}

	return true;
}

UAtumLayerConv1D::UAtumLayerConv1D() noexcept
{
	DimensionCount = 1u;
}

bool UAtumLayerConv1D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module.Reset(new torch::nn::Conv1dImpl(static_cast<torch::nn::Conv1dOptions>(Options)));
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
}

bool UAtumLayerConv2D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module.Reset(new torch::nn::Conv2dImpl(static_cast<torch::nn::Conv2dOptions>(Options)));
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
}

bool UAtumLayerConv3D::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (!Super::OnInitializeData_Implementation(bRetry))
		return false;
	
	Module.Reset(new torch::nn::Conv3dImpl(static_cast<torch::nn::Conv3dOptions>(Options)));
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
