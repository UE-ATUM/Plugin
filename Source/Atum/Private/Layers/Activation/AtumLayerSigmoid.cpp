// © 2023 Kaya Adrian.

#include "Layers/Activation/AtumLayerSigmoid.h"

#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerSigmoid"

bool UAtumLayerSigmoid::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShared<torch::nn::Sigmoid>(std::make_shared<torch::nn::SigmoidImpl>());
	return true;
}

bool UAtumLayerSigmoid::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked()));
	return true;
}

#undef LOCTEXT_NAMESPACE
