// © 2023 Kaya Adrian.

#include "Layers/IAtumLayer.h"

#include "AtumSettings.h"
#include "FunctionLibraries/AtumLibraryUtilities.h"
#include "Tensors/IAtumTensor.h"


#define LOCTEXT_NAMESPACE "IAtumLayer"

IAtumLayer::IAtumLayer() noexcept : bInitialized(false), DimensionCount(0ULL)
{
}

const FAtumLayerBaseOptions* IAtumLayer::GetBaseOptions() const noexcept
{
	return nullptr;
}

FAtumLayerBaseOptions* IAtumLayer::GetBaseOptions() noexcept
{
	return nullptr;
}

std::shared_ptr<torch::nn::Module> IAtumLayer::GetSharedModule() const noexcept
{
	return nullptr;
}

bool IAtumLayer::InitializeData_Implementation(const bool bRetry) noexcept
{
	if (bInitialized && !bRetry)
		return true;
	
	bInitialized = Execute_OnInitializeData(_getUObject(), bRetry);
	return bInitialized;
}

bool IAtumLayer::Forward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
) noexcept
{
	UObject* const LayerObject = _getUObject();
	const ANSICHAR* const LayerClassName = TCHAR_TO_UTF8(*GetNameSafe(LayerObject->GetClass()));
	
	const at::Tensor* const Data = Input ? Input->GetData() : nullptr;
	const at::IntArrayRef& Sizes = Data->sizes();
	
	if (Data == nullptr || Sizes.empty())
	{
		ATUM_LOG(Error, TEXT("Input had no data at ATUM Layer of type `%hs`!"), LayerClassName)
		return false;
	}
	
	for (const int64 Size : Sizes)
	{
		if (UNLIKELY(Size == 0LL))
		{
			ATUM_LOG(Error, TEXT("Input contains 0D dimension in ATUM Layer of type `%hs`!"), LayerClassName)
			return false;
		}
	}
	
	if (!bInitialized)
	{
		ATUM_LOG(Error, TEXT("ATUM Layer of type `%hs` has not been initialized!"), LayerClassName)
		return false;
	}
	
	bool bSuccess;
	try
	{
		bSuccess = Execute_OnForward(LayerObject, Input, Output);
	}
	catch (const std::exception& Exception)
	{
		bSuccess = false;

		const std::string& ExceptionString = Exception.what();
		ATUM_LOG(
			Error,
			TEXT("Unhandled exception - %hs"),
			ExceptionString.substr(0, ExceptionString.find("\n")).c_str()
		)
	}
	
	if (!bSuccess)
	{
		ATUM_LOG(Error, TEXT("Failed to forward in ATUM Layer of type `%hs`!"), LayerClassName)
	}
	return bSuccess;
}

bool IAtumLayer::AreInputSizesValid(const int32 InputSizeCount) const noexcept
{
	if (UNLIKELY(ValidInputSizes.empty()))
	{
		ATUM_LOG(Error, TEXT("No valid input size has been defined for this layer!"))
		return false;
	}
	
	if (!std::ranges::binary_search(ValidInputSizes, InputSizeCount))
	{
		ATUM_LOG(
			Error,
			TEXT("Expected %hs but got %dD input tensor!"),
			UAtumLibraryUtilities::FormatWithConjunction(ValidInputSizes, ", ", "", "D", " or ", false).c_str(),
			InputSizeCount
		)
		return false;
	}
	
	return true;
}

bool IAtumLayer::AreInputSizesValid(const TArray<int64>& InputSizes, const int64 ExpectedChannels) const noexcept
{
	const int32 SizeCount = InputSizes.Num();
	if (!AreInputSizesValid(SizeCount))
		return false;
	
	if (const int64 GivenChannels = InputSizes[SizeCount - DimensionCount - 1]; GivenChannels != ExpectedChannels)
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
	
	return true;
}

bool IAtumLayer::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	ATUM_LOG(Error, TEXT("OnInitializeData is not implemented in `%ls`!"), *GetNameSafe(_getUObject()->GetClass()))
	return false;
}

bool IAtumLayer::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	ATUM_LOG(Error, TEXT("OnForward is not implemented in `%ls`!"), *GetNameSafe(_getUObject()->GetClass()))
	Output = DuplicateObject(Input.GetObject(), nullptr);
	return false;
}

#undef LOCTEXT_NAMESPACE
