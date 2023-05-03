// © 2023 Kaya Adrian.

#include "Layers/Convolution/AtumLayerConvTranspose.h"


CONSTEXPR uint64 UAtumLayerConvTranspose::GetDimensionCount() const noexcept
{
	return 0u;
}

bool UAtumLayerConvTranspose::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	if (const int64 Groups = Options.Groups; Options.InChannels % Groups != 0 || Options.OutChannels % Groups != 0)
	{
		UE_LOG(LogAtum, Error, TEXT("Input and output channels must both be divisible by the group count!"))
		return false;
	}
	
	const TArray<int64>& KernelSize = Options.KernelSize;
	const TArray<int64>& Stride = Options.Stride;
	const TArray<int64>& Padding = Options.Padding;
	const TArray<int64>& OutputPadding = Options.OutputPadding;
	const TArray<int64>& Dilation = Options.Dilation;
	
	const uint64 DimensionCount = GetDimensionCount();
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

CONSTEXPR uint64 UAtumLayerConvTranspose1D::GetDimensionCount() const noexcept
{
	return 1u;
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
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	const int32 SizeCount = InputSizes.Num();
	if (SizeCount != 2 && SizeCount != 3)
	{
		UE_LOG(LogAtum, Error, TEXT("ConvTranspose1D - Expected 2D or 3D input but got %dD!"), SizeCount)
		return false;
	}

	const int64 GivenChannels = InputSizes[SizeCount - 2];
	if (const int64 ExpectedChannels = Module->options.in_channels(); GivenChannels != ExpectedChannels)
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("ConvTranspose1D - Expected %lld channels but got %lld!"),
			ExpectedChannels,
			GivenChannels
		)
		return false;
	}
	
	const int64 InputLength = InputSizes[SizeCount - 1];
	if (const int64 OutputLength = FindOutputDimension(InputLength, 0); OutputLength < 0)
	{
		UE_LOG(LogAtum, Error, TEXT("ConvTranspose1D - Calculated output (%lld) is invalid!"), OutputLength)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

CONSTEXPR uint64 UAtumLayerConvTranspose2D::GetDimensionCount() const noexcept
{
	return 2u;
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
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	const int32 SizeCount = InputSizes.Num();
	if (SizeCount != 3 && SizeCount != 4)
	{
		UE_LOG(LogAtum, Error, TEXT("ConvTranspose2D - Expected 3D or 4D input but got %dD!"), SizeCount)
		return false;
	}

	const int64 GivenChannels = InputSizes[SizeCount - 3];
	if (const int64 ExpectedChannels = Module->options.in_channels(); GivenChannels != ExpectedChannels)
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("ConvTranspose2D - Expected %lld channels but got %lld!"),
			ExpectedChannels,
			GivenChannels
		)
		return false;
	}
	
	const int64 InputHeight = InputSizes[SizeCount - 2];
	const int64 InputWidth = InputSizes[SizeCount - 1];
	
	const int64 OutputHeight = FindOutputDimension(InputHeight, 0);
	if (const int64 OutputWidth = FindOutputDimension(InputWidth, 1); OutputHeight < 0 || OutputWidth < 0)
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("ConvTranspose2D - Calculated output (%lld x %lld) is invalid!"),
			OutputHeight,
			OutputWidth
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

CONSTEXPR uint64 UAtumLayerConvTranspose3D::GetDimensionCount() const noexcept
{
	return 3u;
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
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	const int32 SizeCount = InputSizes.Num();
	if (SizeCount != 4 && SizeCount != 5)
	{
		UE_LOG(LogAtum, Error, TEXT("ConvTranspose3D - Expected 4D or 5D input but got %dD!"), SizeCount)
		return false;
	}

	const int64 GivenChannels = InputSizes[SizeCount - 4];
	if (const int64 ExpectedChannels = Module->options.in_channels(); GivenChannels != ExpectedChannels)
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("ConvTranspose3D - Expected %lld channels but got %lld!"),
			ExpectedChannels,
			GivenChannels
		)
		return false;
	}

	const int64 InputDepth = InputSizes[SizeCount - 3];
	const int64 InputHeight = InputSizes[SizeCount - 2];
	const int64 InputWidth = InputSizes[SizeCount - 1];
	
	const int64 OutputDepth = FindOutputDimension(InputDepth, 0);
	const int64 OutputHeight = FindOutputDimension(InputHeight, 1);
	if (
		const int64 OutputWidth = FindOutputDimension(InputWidth, 2);
		OutputDepth < 0 || OutputHeight < 0 || OutputWidth < 0
	)
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("ConvTranspose3D - Calculated output (%lld x %lld x %lld) is invalid!"),
			OutputDepth,
			OutputHeight,
			OutputWidth
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}
