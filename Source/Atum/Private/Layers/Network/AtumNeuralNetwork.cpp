// © 2023 Kaya Adrian.

#include "Layers/Network/AtumNeuralNetwork.h"

#include "AtumSettings.h"
#include "Layers/Network/AtumNeuralNetworkLayers.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetwork"

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	AtumNetworkImpl::AtumNetworkImpl(const AtumNetworkOptions& options_) noexcept : options(options_)
	{
	}
	
	void AtumNetworkImpl::reset()
	{
		options = AtumNetworkOptions();
	}
	
	void AtumNetworkImpl::pretty_print(std::ostream& stream) const
	{
		stream << "torch::nn::AtumNetwork";
	}
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning

bool UAtumNeuralNetwork::RegisterLayerAt(const TScriptInterface<IAtumLayer>& Layer, const int32 Index) noexcept
{
	if (Index < 0)
	{
		ATUM_LOG(Error, TEXT("The number %d is not a valid index!"), Index)
		return false;
	}
	
	if (Layer == nullptr || !Execute_InitializeData(Layer.GetObject(), false))
	{
		ATUM_LOG(Error, TEXT("Could not register uninitialized layer in `%ls` ATUM Neural Network!"), *GetName())
		return false;
	}
	
	RegisteredLayers.Insert(Layer, Index);
	return true;
}

bool UAtumNeuralNetwork::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::AtumNetwork(std::make_shared<torch::nn::AtumNetworkImpl>(
		static_cast<torch::nn::AtumNetworkOptions>(Options)
	)));
	
	const TObjectPtr<UAtumNeuralNetworkLayers> Data = Options.LayersData;
	if (Data == nullptr)
		return true;
	
	TArray<TObjectPtr<const UObject>> Layers;
	Data->GetLayerObjects(Layers);
	
	const TArray<TScriptInterface<IAtumLayer>> PriorLayers = RegisteredLayers;
	for (const TObjectPtr<const UObject> Layer : Layers)
	{
		if (!RegisterLayer(DuplicateObject<UObject>(Layer, this)))
		{
			ATUM_LOG(Error, TEXT("Network `%ls` cannot register layers using `%ls`!"), *GetName(), *Data->GetName())
			RegisteredLayers = PriorLayers;
			return false;
		}
	}
	
	return true;
}

bool UAtumNeuralNetwork::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TScriptInterface<IAtumTensor> Subinput = Input;
	for (const TScriptInterface<IAtumLayer>& RegisteredLayer : RegisteredLayers)
	{
		UObject* const Layer = RegisteredLayer.GetObject();
		if (Layer == this)
		{
			ATUM_LOG(Warning, TEXT("Neural network `%ls` contains itself as a layer!"), *GetName())
			continue;
		}
		
		if (Layer == nullptr || !Execute_Forward(Layer, Subinput, Output))
			return false;
		
		Subinput = Output;
	}
	
	return true;
}

#undef LOCTEXT_NAMESPACE
