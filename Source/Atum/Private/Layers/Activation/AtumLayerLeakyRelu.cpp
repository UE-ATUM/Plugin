// © 2023 Kaya Adrian.

#include "Layers/Activation/AtumLayerLeakyRelu.h"

#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerLeakyRelu"

bool UAtumLayerLeakyRelu::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShared<torch::nn::LeakyReLU>(std::make_shared<torch::nn::LeakyReLUImpl>(
		static_cast<torch::nn::LeakyReLUOptions>(Options)
	));
	return true;
}

bool UAtumLayerLeakyRelu::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kDouble)));
	return true;
}

bool UAtumLayerLeakyRelu::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!IAtumLayer::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

#undef LOCTEXT_NAMESPACE
