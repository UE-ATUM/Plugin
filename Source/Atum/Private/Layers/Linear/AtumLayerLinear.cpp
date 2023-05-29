// © 2023 Kaya Adrian.

#include "Layers/Linear/AtumLayerLinear.h"

#include "Macros/AtumMacrosLog.h"
#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerLinear"

bool UAtumLayerLinear::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	if (Options.InFeatures <= 0LL)
	{
		ATUM_LOG(Error, TEXT("There must exist at least 1 input feature!"))
		return false;
	}
	if (Options.OutFeatures <= 0LL)
	{
		ATUM_LOG(Error, TEXT("There must exist at least 1 output feature!"))
		return false;
	}
	
	Module = MakeShared<torch::nn::Linear>(std::make_shared<torch::nn::LinearImpl>(
		static_cast<torch::nn::LinearOptions>(Options)
	));
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
		ATUM_LOG(Error, TEXT("Cannot use 0D input tensor!"))
		return false;
	}
	
	const int64 GivenChannels = InputSizes.Last();
	if (const int64 ExpectedChannels = Options.InFeatures; GivenChannels != ExpectedChannels)
	{
		ATUM_LOG(
			Error,
			TEXT("Expected %lld %ls but got %lld!"),
			ExpectedChannels,
			ExpectedChannels == 1LL ? TEXT("channel") : TEXT("channels"),
			GivenChannels
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kFloat)));
	return true;
}

#undef LOCTEXT_NAMESPACE
