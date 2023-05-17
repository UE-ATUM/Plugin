// © 2023 Kaya Adrian.

#include "Layers/Linear/AtumLayerLinear.h"

#include "IAtum.h"


bool UAtumLayerLinear::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module->options = static_cast<torch::nn::LinearOptions>(Options);
	return true;
}

bool UAtumLayerLinear::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	if (InputSizes.IsEmpty())
	{
		UE_LOG(LogAtum, Error, TEXT("Cannot use 0D input tensor!"))
		return false;
	}
	
	const int64 GivenChannels = InputSizes.Last();
	if (const int64 ExpectedChannels = Options.InFeatures; GivenChannels != ExpectedChannels)
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("Expected %lld %ls but got %lld!"),
			ExpectedChannels,
			ExpectedChannels == 1 ? TEXT("channel") : TEXT("channels"),
			GivenChannels
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData(Module->forward(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}
