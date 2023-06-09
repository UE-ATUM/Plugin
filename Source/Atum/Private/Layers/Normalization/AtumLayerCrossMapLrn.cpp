﻿// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerCrossMapLrn.h"

#include "Macros/AtumMacrosLog.h"
#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerCrossMapLrn"

UAtumLayerCrossMapLrn2D::UAtumLayerCrossMapLrn2D() noexcept
{
	DimensionCount = 2ULL;
	ValidInputSizes.push_back(4LL);
}

bool UAtumLayerCrossMapLrn2D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	if (const int64 Size = Options.Size; Size <= 0LL)
	{
		ATUM_LOG(Error, TEXT("Got size %lld, which is not positive!"), Size)
		return false;
	}
	
	Module = MakeShared<torch::nn::CrossMapLRN2d>(std::make_shared<torch::nn::CrossMapLRN2dImpl>(
		static_cast<torch::nn::CrossMapLRN2dOptions>(Options)
	));
	return true;
}

bool UAtumLayerCrossMapLrn2D::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	if (!AreInputSizesValid(InputSizes.Num()))
		return false;
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

bool UAtumLayerCrossMapLrn2D::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!IAtumLayer::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

#undef LOCTEXT_NAMESPACE
