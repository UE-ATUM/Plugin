// © 2023 Kaya Adrian.

#include "Layers/Activation/AtumLayerRelu.h"

#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerRelu"

bool UAtumLayerRelu::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::ReLU(std::make_shared<torch::nn::ReLUImpl>(
		static_cast<torch::nn::ReLUOptions>(Options)
	)));
	return true;
}

bool UAtumLayerRelu::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kDouble)));
	return true;
}

#undef LOCTEXT_NAMESPACE
