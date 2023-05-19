// © 2023 Kaya Adrian.

#include "AtumNeuralNetwork.h"

#include "AtumSettings.h"


// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	void AtumNetworkImpl::reset()
	{
	}

	void AtumNetworkImpl::pretty_print(std::ostream& stream) const
	{
		stream << "torch::nn::AtumNetwork";
	}
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning

UAtumNeuralNetwork::UAtumNeuralNetwork() noexcept
{
	NamedLayers.Add(TEXT("Network Input"), this);
}

void UAtumNeuralNetwork::RegisterLayer(const FName Name, const TScriptInterface<IAtumLayer>& Layer) noexcept
{
	const ANSICHAR* const NetworkName = TCHAR_TO_UTF8(*GetNameSafe(this));
	if (UNLIKELY(!Execute_InitializeData(this, false)))
	{
		ATUM_LOG(Error, TEXT("Could not initialize ATUM Neural Network instance called `%hs`!"), NetworkName)
		return;
	}
	
	if (Layer == nullptr || !Layer->IsInitialized())
	{
		ATUM_LOG(Error, TEXT("Could not register uninitialized layer in `%hs` ATUM Neural Network!"), NetworkName)
		return;
	}
	
	NamedLayers.Add(Name, Layer);
}

bool UAtumNeuralNetwork::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::AtumNetwork(std::make_shared<torch::nn::AtumNetworkImpl>()));
	return true;
}

bool UAtumNeuralNetwork::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	bool bHasActualLayers = false;
	TScriptInterface<IAtumTensor> Subinput = Input;
	
	for (const TTuple<FName, TScriptInterface<IAtumLayer>>& NamedLayer : NamedLayers)
	{
		const TScriptInterface<IAtumLayer>& Layer = NamedLayer.Value;
		if (Layer == this)
			continue;

		bHasActualLayers = true;
		if (!Execute_Forward(Layer ? Layer->_getUObject() : nullptr, Subinput, Output))
			return false;
		
		Subinput = Output;
	}
	
	return bHasActualLayers;
}
