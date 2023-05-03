// © 2023 Kaya Adrian.

#include "Layers/IAtumLayer.h"

#include "IAtum.h"


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
			TEXT("Unhandled exception in ATUM Layer of type `%hs` - %hs"),
			LayerClassName,
			ExceptionString.substr(0, ExceptionString.find("\n")).c_str()
		)
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
