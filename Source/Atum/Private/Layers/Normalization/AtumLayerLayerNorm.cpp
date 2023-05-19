// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerLayerNorm.h"

#include "AtumSettings.h"
#include "FunctionLibraries/AtumLibraryUtilities.h"


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
		(*Module)->options.normalized_shape().~vector();
	}
}

bool UAtumLayerLayerNorm::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	DestroyNormalizedShape();
	
	if (Options.NormalizedShape.IsEmpty())
	{
		ATUM_LOG(Error, TEXT("Normalized Shape must contain at least 1 dimension!"))
		return false;
	}
	
	Module.Reset(new torch::nn::LayerNorm(std::make_shared<torch::nn::LayerNormImpl>(
		static_cast<torch::nn::LayerNormOptions>(Options)
	)));
	return true;
}

bool UAtumLayerLayerNorm::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	
	const int64* const NormalizedShapeData = Options.NormalizedShape.GetData();
	const int32 NormalizedShapeCount = Options.NormalizedShape.Num();
	
	if (const int32 GivenShapeSizeCount = InputSizes.Num() - 1; GivenShapeSizeCount != NormalizedShapeCount)
	{
		ATUM_LOG(Error, TEXT("Expected %dD input, got %dD!"), NormalizedShapeCount, GivenShapeSizeCount)
		return false;
	}
	
	bool bMismatchedSizes = false;
	std::vector<int64> InputSizesVector(NormalizedShapeCount);
	const std::vector NormalizedShapeVector(NormalizedShapeData, NormalizedShapeData + NormalizedShapeCount);
	
	for (int32 Index = 0; Index < NormalizedShapeCount; ++Index)
	{
		InputSizesVector[Index] = InputSizes[Index + 1];
		
		bMismatchedSizes |= NormalizedShapeVector[Index] != InputSizesVector[Index];
	}
	if (bMismatchedSizes)
	{
		ATUM_LOG(
			Error,
			TEXT("Input tensor of shape (%hs) doesn't match the expected (%hs) normalized shape!"),
			UAtumLibraryUtilities::FormatWithConjunction(InputSizesVector, " x ").c_str(),
			UAtumLibraryUtilities::FormatWithConjunction(NormalizedShapeVector, " x ").c_str()
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}
