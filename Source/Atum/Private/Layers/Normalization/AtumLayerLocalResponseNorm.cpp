// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerLocalResponseNorm.h"

#include "AtumSettings.h"
#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerLocalResponseNorm"

bool UAtumLayerLocalResponseNorm::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	if (const int64 Size = Options.Size; Size <= 0LL)
	{
		ATUM_LOG(Error, TEXT("Got size %lld, which is not positive!"), Size)
		return false;
	}
	
	Module = MakeShared<torch::nn::LocalResponseNorm>(std::make_shared<torch::nn::LocalResponseNormImpl>(
		static_cast<torch::nn::LocalResponseNormOptions>(Options)
	));
	return true;
}

bool UAtumLayerLocalResponseNorm::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	if (const int32 SizeCount = InputSizes.Num(); SizeCount < 3)
	{
		ATUM_LOG(Error, TEXT("Expected 3D or higher dimensionality input but got a %dD tensor!"), SizeCount)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kDouble)));
	return true;
}

#undef LOCTEXT_NAMESPACE
