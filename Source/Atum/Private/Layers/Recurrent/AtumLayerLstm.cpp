// © 2023 Kaya Adrian.

#include "Layers/Recurrent/AtumLayerLstm.h"

#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerLstm"

UAtumLayerLstm::UAtumLayerLstm() noexcept : HiddenLayer(nullptr)
{
}

bool UAtumLayerLstm::OnInitializeData_Implementation(const bool bRetry)
{
	if (bRetry)
	{
		HiddenLayer = nullptr;
	}
	
	Module = MakeShared<torch::nn::LSTM>(std::make_shared<torch::nn::LSTMImpl>(
		static_cast<torch::nn::LSTMOptions>(Options)
	));
	return true;
}

bool UAtumLayerLstm::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	std::tuple<at::Tensor, std::tuple<at::Tensor, at::Tensor>> LstmOutputs = (*Module)->forward(
		Input->GetDataChecked(),
		HiddenLayer ? *HiddenLayer : std::tuple<at::Tensor, at::Tensor>()
	);
	HiddenLayer = TSharedPtr<std::tuple<at::Tensor, at::Tensor>>(&std::get<1ULL>(LstmOutputs));
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(std::get<0ULL>(LstmOutputs).squeeze(0LL));
	return true;
}

bool UAtumLayerLstm::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!IAtumLayer::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

#undef LOCTEXT_NAMESPACE
