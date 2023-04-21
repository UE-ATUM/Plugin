// © 2023 Kaya Adrian.

#include "Layers/AtumLayerLinear.h"

#include "IAtum.h"


UAtumLayerLinear::UAtumLayerLinear() noexcept : InFeatures(1), OutFeatures(1), bLearnBias(true)
{
}

bool UAtumLayerLinear::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::LinearImpl(InFeatures, OutFeatures));
	Module->options.bias(bLearnBias);
	return true;
}

bool UAtumLayerLinear::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
) noexcept
{
	torch::Tensor NewTensorData;
	try
	{
		NewTensorData = Module->forward(Input->GetDataChecked().toType(Module->weight.scalar_type()));
	}
	catch (const c10::Error& Error)
	{
		UE_LOG(LogAtum, Error, TEXT("%hs"), Error.what_without_backtrace())
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(NewTensorData);
	return true;
}
