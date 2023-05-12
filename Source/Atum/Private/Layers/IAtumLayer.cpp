// © 2023 Kaya Adrian.

#include "Layers/IAtumLayer.h"

#include "AtumLibraryUtilities.h"
#include "IAtum.h"


IAtumLayer::IAtumLayer() noexcept : bInitialized(false), DimensionCount(0u), ValidInputSizes(std::vector<int64>())
{
}

bool IAtumLayer::AreInputSizesValid(const TArray<int64>& InputSizes, const int64 ExpectedChannels) const noexcept
{
	if (UNLIKELY(ValidInputSizes.empty()))
	{
		UE_LOG(LogAtum, Error, TEXT("No valid input size has been defined for this layer!"))
		return false;
	}

	const int32 SizeCount = InputSizes.Num();
	if (!std::ranges::binary_search(ValidInputSizes, SizeCount))
	{
		UE_LOG(
			LogAtum,
			Error,
			TEXT("Expected %hs but got %dD input tensor!"),
			UAtumLibraryUtilities::FormatWithConjunction(ValidInputSizes, ", ", "", "D", " or ", false).c_str(),
			SizeCount
		)
		return false;
	}

	if (const int64 GivenChannels = InputSizes[SizeCount - DimensionCount - 1]; GivenChannels != ExpectedChannels)
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

	return true;
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

	if (const torch::Tensor* const Data = Input ? Input->GetData() : nullptr; Data == nullptr)
	{
		UE_LOG(LogAtum, Error, TEXT("Input had no data at ATUM Layer of type `%hs`!"), LayerClassName)
		return false;
	}
	
	if (!Execute_InitializeData(LayerObject, false))
	{
		UE_LOG(LogAtum, Error, TEXT("Could not initialize ATUM Layer of type `%hs`!"), LayerClassName)
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
		UE_LOG(
			LogAtum,
			Error,
			TEXT("Unhandled exception - %hs"),
			ExceptionString.substr(0, ExceptionString.find("\n")).c_str()
		)
	}

	if (!bSuccess)
	{
		UE_LOG(LogAtum, Error, TEXT("Failed to forward in ATUM Layer of type `%hs`!"), LayerClassName)
	}
	return bSuccess;
}

bool IAtumLayer::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	const ANSICHAR* const LayerClassName = TCHAR_TO_UTF8(*GetNameSafe(_getUObject()->GetClass()));
	UE_LOG(LogAtum, Error, TEXT("OnInitializeData is not implemented in `%hs`!"), LayerClassName)
	
	return false;
}

bool IAtumLayer::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	const ANSICHAR* const LayerClassName = TCHAR_TO_UTF8(*GetNameSafe(_getUObject()->GetClass()));
	UE_LOG(LogAtum, Error, TEXT("OnForward is not implemented in `%hs`!"), LayerClassName)
	
	Output = DuplicateObject(Input.GetObject(), nullptr);
	return false;
}
