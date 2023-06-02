// © 2023 Kaya Adrian.

#include "Layers/Activation/AtumLayerTanh.h"

#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerTanh"

bool UAtumLayerTanh::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShared<torch::nn::Tanh>(std::make_shared<torch::nn::TanhImpl>());
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

bool UAtumLayerTanh::LoadFromFile_Implementation(const FString& RelativePath)
{
	return IAtumLayer::LoadFromFile_Implementation(RelativePath);
}

#undef LOCTEXT_NAMESPACE
