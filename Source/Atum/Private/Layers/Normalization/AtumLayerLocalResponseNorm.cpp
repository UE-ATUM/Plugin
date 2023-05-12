// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerLocalResponseNorm.h"

#include "IAtum.h"


bool UAtumLayerLocalResponseNorm::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	if (const int64 Size = Options.Size; Size <= 0)
	{
		UE_LOG(LogAtum, Error, TEXT("Got size %lld, which is not positive!"), Size)
		return false;
	}
	
	MakeModule<torch::nn::LocalResponseNormOptions>(Options);
	return true;
}

bool UAtumLayerLocalResponseNorm::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked()));
	return true;
}
