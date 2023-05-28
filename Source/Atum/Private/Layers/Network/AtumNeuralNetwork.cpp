// © 2023 Kaya Adrian.

#include "Layers/Network/AtumNeuralNetwork.h"

#include "AtumSettings.h"
#include "Layers/Network/AtumNeuralNetworkLayers.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetwork"

#if WITH_EDITOR
const TUniquePtr<UAtumNeuralNetwork::FOnPostCDOCompiled> UAtumNeuralNetwork::OnPostCDOCompiled =
	MakeUnique<FOnPostCDOCompiled>();
#endif


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

	UObject* const LayerObject = Layer.GetObject();
	if (LayerObject == nullptr || !Execute_InitializeData(LayerObject, true))
	{
		ATUM_LOG(Error, TEXT("Could not register uninitialized layer in `%ls` ATUM Neural Network!"), *GetName())
		return false;
	}
	
	RegisteredLayers.Insert(LayerObject, Index);
	return true;
}

const TArray<const UObject*>& UAtumNeuralNetwork::GetRegisteredLayers() const noexcept
{
	RegisteredLayersConst.Empty(RegisteredLayers.Num());
	for (const TObjectPtr<UObject> RegisteredLayer : RegisteredLayers)
	{
		TScriptInterface<IAtumLayer> DuplicateLayer;
		Execute_CloneData(RegisteredLayer.Get(), DuplicateLayer, GetTransientPackage());
		RegisteredLayersConst.Add(DuplicateLayer.GetObject());
	}
	return RegisteredLayersConst;
}

bool UAtumNeuralNetwork::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	RegisteredLayers.Empty();
	const TObjectPtr<UAtumNeuralNetworkLayers> Data = Options.LayersData;
	
	const TArray<const UObject*>& Layers = Data ? Data->GetLayerObjects() : TArray<const UObject*>();
	const int32 LayerCount = Layers.Num();
	
	for (int32 Index = 0; Index < LayerCount; ++Index)
	{
		if (!RegisterLayer(DuplicateObject<UObject>(Layers[Index], this)))
		{
			ATUM_LOG(
				Error,
				TEXT("Network `%ls` cannot register layers using `%ls` due to an issue at index %d!"),
				*GetName(),
				*Data->GetName(),
				Index
			)
			RegisteredLayers.Empty();
			return false;
		}
	}
	
	Module = MakeShared<torch::nn::AtumNetwork>(std::make_shared<torch::nn::AtumNetworkImpl>(
		static_cast<torch::nn::AtumNetworkOptions>(Options)
	));
	return true;
}

bool UAtumNeuralNetwork::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TScriptInterface<IAtumTensor> Subinput = Input;

	const int32 RegisteredLayerCount = RegisteredLayers.Num();
	for (int32 Index = 0; Index < RegisteredLayerCount; ++Index)
	{
		UObject* const LayerObject = RegisteredLayers[Index].Get();
		if (LayerObject == this)
		{
			ATUM_LOG(Warning, TEXT("Neural network `%ls` contains itself as a layer!"), *GetName())
			continue;
		}
		
		if (LayerObject == nullptr || !Execute_Forward(LayerObject, Subinput, Output))
		{
			ATUM_LOG(Error, TEXT("Error encountered at registered layer number %d!"), Index)
			return false;
		}
		
		Subinput = Output;
	}
	
	return true;
}

void UAtumNeuralNetwork::GetParameters_Implementation(
	const UClass* const Class,
	TMap<FString, TScriptInterface<IAtumTensor>>& OutValues
) const noexcept
{
	IAtumLayer::GetParameters_Implementation(Class, OutValues);
	for (const TObjectPtr<UObject> RegisteredLayer : RegisteredLayers)
	{
		Execute_GetParameters(RegisteredLayer.Get(), Class, OutValues);
	}
}

#if WITH_EDITOR
void UAtumNeuralNetwork::PostCDOCompiled(const FPostCDOCompiledContext& Context)
{
	Super::PostCDOCompiled(Context);
	
	OnPostCDOCompiled->Broadcast();
}
#endif

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
void UAtumNeuralNetwork::execGetRegisteredLayers(
	UObject* const Context,
	FFrame& Stack,
	void* const Z_Param__Result
) noexcept
{
	P_FINISH
	
	P_NATIVE_BEGIN
	*static_cast<TArray<const UObject*>*>(Z_Param__Result) = P_THIS->GetRegisteredLayers();
	P_NATIVE_END
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning

#undef LOCTEXT_NAMESPACE
