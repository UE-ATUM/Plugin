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
	const TCHAR* const LayerClassName = *LayerObject->GetClass()->GetName();

	if (const torch::Tensor* const Data = Input ? Input->GetData() : nullptr; Data == nullptr)
	{
		UE_LOG(LogAtum, Error, TEXT("Input had no data at ATUM Layer of type %s!"), LayerClassName)
		return false;
	}
	
	if (!Execute_InitializeData(LayerObject, false))
	{
		UE_LOG(LogAtum, Error, TEXT("Could not initialize ATUM Layer of type %s!"), LayerClassName)
		return false;
	}
	
	return Execute_OnForward(LayerObject, Input, Output);
}

bool IAtumLayer::OnInitializeData_Implementation(const bool bRetry) noexcept
{
	return false;
}

bool IAtumLayer::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
) noexcept
{
	Output = DuplicateObject(Input.GetObject(), nullptr);
	return false;
}
