// © 2023 Kaya Adrian.

#include "Layers/AtumLayerLinear.h"

#include "IAtum.h"


UAtumLayerLinear::UAtumLayerLinear() noexcept : InFeatures(1), OutFeatures(1), bLearnBias(true)
{
}

bool UAtumLayerLinear::InitializeData_Implementation() noexcept
{
	if (UNLIKELY(!IAtumLayer::InitializeData_Implementation()))
		return false;
	
	Module.Reset(new torch::nn::LinearImpl(InFeatures, OutFeatures));
	Module->options.bias(bLearnBias);
	return true;
}

bool UAtumLayerLinear::Forward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
) noexcept
{
	if (UNLIKELY(!Execute_IsInitialized(this)))
	{
		UE_LOG(LogAtum, Fatal, TEXT("InitializeData was not called for object of type %s!"), *GetClass()->GetName())
		return false;
	}
	
	const torch::Tensor* const Data = Input ? Input->GetData() : nullptr;
	if (Data == nullptr)
		return false;
	
	torch::Tensor NewTensorData;
	try
	{
		NewTensorData = Module->forward(Data->toType(Module->weight.scalar_type()));
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
