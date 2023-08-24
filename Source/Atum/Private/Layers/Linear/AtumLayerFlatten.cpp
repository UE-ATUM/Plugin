// © 2023 Kaya Adrian.

#include "Layers/Linear/AtumLayerFlatten.h"

#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerFlatten"

bool UAtumLayerFlatten::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Module = MakeShared<torch::nn::Flatten>(std::make_shared<torch::nn::FlattenImpl>(
		static_cast<torch::nn::FlattenOptions>(Options)
	));
	return true;
}

bool UAtumLayerFlatten::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked()));
	return true;
}

bool UAtumLayerFlatten::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!IAtumLayer::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

#undef LOCTEXT_NAMESPACE
