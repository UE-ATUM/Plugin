// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerGroupNorm.h"

#include "AtumSettings.h"
#include "Tensors/IAtumTensor.h"


bool UAtumLayerGroupNorm::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	const int64 Groups = Options.NumGroups;
	const int64 Channels = Options.NumChannels;

	bool bPositiveValues = true;
	if (Groups <= 0)
	{
		ATUM_LOG(Error, TEXT("There must exist at least 1 group!"))
		bPositiveValues = false;
	}
	if (Channels <= 0)
	{
		ATUM_LOG(Error, TEXT("There must exist at least 1 channel!"))
		bPositiveValues = false;
	}
	if (!bPositiveValues)
		return false;
	
	if (Channels % Groups != 0)
	{
		ATUM_LOG(Error, TEXT("The number of channels must be divisible by the number of groups!"))
		return false;
	}
	
	Module.Reset(new torch::nn::GroupNorm(std::make_shared<torch::nn::GroupNormImpl>(
		static_cast<torch::nn::GroupNormOptions>(Options)
	)));
	return true;
}

bool UAtumLayerGroupNorm::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);
	if (const int32 SizeCount = InputSizes.Num(); SizeCount < 2)
	{
		ATUM_LOG(Error, TEXT("Expected 2D or higher dimensionality input but got a %dD tensor!"), SizeCount)
		return false;
	}

	const int64 ExpectedChannels = Options.NumChannels;
	if (const int64 GivenChannels = InputSizes[1]; GivenChannels != ExpectedChannels)
	{
		ATUM_LOG(
			Error,
			TEXT("Expected %lld %ls but got %lld!"),
			ExpectedChannels,
			ExpectedChannels == 1 ? TEXT("channel") : TEXT("channels"),
			GivenChannels
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}
