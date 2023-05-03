// © 2023 Kaya Adrian.

#include "Layers/AtumLayerLinear.h"

#include "IAtum.h"


FAtumOptionsLinear::FAtumOptionsLinear() noexcept : InFeatures(0), OutFeatures(0), bBias(true)
{
}

FAtumOptionsLinear::operator torch::nn::LinearOptions() const noexcept
{
	return torch::nn::LinearOptions(InFeatures, OutFeatures).bias(bBias);
}

bool UAtumLayerLinear::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::LinearImpl(static_cast<torch::nn::LinearOptions>(Options)));
	return true;
}

bool UAtumLayerLinear::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	const int64 GivenFeatures = InputSizes.Last();
	
	if (const int64 ExpectedFeatures = Module->options.in_features(); GivenFeatures != ExpectedFeatures)
	{
		UE_LOG(LogAtum, Error, TEXT("Linear - Expected %lld features but got %lld!"), ExpectedFeatures, GivenFeatures)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}
