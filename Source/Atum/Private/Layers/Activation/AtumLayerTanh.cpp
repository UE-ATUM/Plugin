// © 2023 Kaya Adrian.

#include "Layers/Activation/AtumLayerTanh.h"

#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerTanh"

bool UAtumLayerTanh::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::Tanh(std::make_shared<torch::nn::TanhImpl>()));
	return true;
}

bool UAtumLayerTanh::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked()));
	return true;
}

#undef LOCTEXT_NAMESPACE
