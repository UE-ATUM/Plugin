// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerGroupNorm.h"

#include "Macros/AtumMacrosLog.h"
#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "AtumLayerGroupNorm"

bool UAtumLayerGroupNorm::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	const int64 Groups = Options.NumGroups;
	const int64 Channels = Options.NumChannels;

	bool bPositiveValues = true;
	if (Groups <= 0LL)
	{
		ATUM_LOG(Error, TEXT("There must exist at least 1 group!"))
		bPositiveValues = false;
	}
	if (Channels <= 0LL)
	{
		ATUM_LOG(Error, TEXT("There must exist at least 1 channel!"))
		bPositiveValues = false;
	}
	if (!bPositiveValues)
		return false;
	
	if (Channels % Groups != 0LL)
	{
		ATUM_LOG(Error, TEXT("The number of channels must be divisible by the number of groups!"))
		return false;
	}
	
	Module = MakeShared<torch::nn::GroupNorm>(std::make_shared<torch::nn::GroupNormImpl>(
		static_cast<torch::nn::GroupNormOptions>(Options)
	));
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
			ExpectedChannels == 1LL ? TEXT("channel") : TEXT("channels"),
			GivenChannels
		)
		return false;
	}
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	Output->SetData((*Module)(Input->GetDataChecked().to(c10::kBFloat16)));
	return true;
}

bool UAtumLayerGroupNorm::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!IAtumLayer::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom((*Module)->options);
	return true;
}

#undef LOCTEXT_NAMESPACE
