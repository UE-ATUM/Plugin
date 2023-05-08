// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerLayerNorm.h"

#include "IAtum.h"


UAtumLayerLayerNorm::~UAtumLayerLayerNorm() noexcept
{
	if (Module)
	{
		DestroyNormalizedShape();
	}
}

void UAtumLayerLayerNorm::DestroyNormalizedShape() const noexcept
{
	if (bInitialized)
	{
		Module->options.normalized_shape().~vector();
	}
}

bool UAtumLayerLayerNorm::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	DestroyNormalizedShape();
	
	if (Options.NormalizedShape.IsEmpty())
	{
		UE_LOG(LogAtum, Error, TEXT("Normalized Shape must contain at least 1 dimension!"))
		return false;
	}
	
	MakeModule<torch::nn::LayerNormOptions>(Options);
	return true;
}

bool UAtumLayerLayerNorm::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	
	const int32 SizeCount = InputSizes.Num();
	if (SizeCount == 0)
	{
		UE_LOG(LogAtum, Error, TEXT("Cannot use 0D input tensor!"))
		return false;
	}

	const TArray<int64>& NormalizedShape = Options.NormalizedShape;
	const int32 NormalizedShapeSizeCount = NormalizedShape.Num();
	
	if (const int32 GivenShapeSizeCount = SizeCount - 1; GivenShapeSizeCount != NormalizedShapeSizeCount)
	{
		UE_LOG(LogAtum, Error, TEXT("Expected %dD input, got %dD!"), NormalizedShapeSizeCount, GivenShapeSizeCount)
		return false;
	}
	
	for (int32 Index = 0; Index < NormalizedShapeSizeCount; ++Index)
	{
		if (NormalizedShape[Index] != InputSizes[Index + 1])
		{
			UE_LOG(LogAtum, Error, TEXT("Input tensor shape values don't match the expected normalized shape's!"))
			return false;
		}
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}
