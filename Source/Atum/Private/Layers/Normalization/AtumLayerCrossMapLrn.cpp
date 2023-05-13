// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerCrossMapLrn.h"

#include "IAtum.h"


UAtumLayerCrossMapLrn2D::UAtumLayerCrossMapLrn2D() noexcept
{
	DimensionCount = 2u;
	ValidInputSizes.push_back(4);
}

bool UAtumLayerCrossMapLrn2D::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	if (const int64 Size = Options.Size; Size <= 0)
	{
		UE_LOG(LogAtum, Error, TEXT("Got size %lld, which is not positive!"), Size)
		return false;
	}
	
	MakeModule<torch::nn::CrossMapLRN2dOptions>(Options);
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
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}
