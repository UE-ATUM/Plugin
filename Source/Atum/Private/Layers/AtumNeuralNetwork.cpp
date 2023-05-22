// © 2023 Kaya Adrian.

#include "Layers/AtumNeuralNetwork.h"

#include "AtumSettings.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetwork"

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

UAtumNeuralNetwork::UAtumNeuralNetwork() noexcept : NetworkLayerName(TEXT("ATUM Network"))
{
}

void UAtumNeuralNetwork::RegisterLayer(const FName Name, const TScriptInterface<IAtumLayer>& Layer) noexcept
{
	const ANSICHAR* const NetworkName = TCHAR_TO_UTF8(*GetNameSafe(this));
	if (UNLIKELY(!Execute_InitializeData(this, false)))
	{
		ATUM_LOG(Error, TEXT("Could not initialize ATUM Neural Network instance called `%hs`!"), NetworkName)
		return;
	}
	
	UObject* const LayerObject = Layer.GetObject();
	if (LayerObject == nullptr || !Layer->IsInitialized())
	{
		ATUM_LOG(Error, TEXT("Could not register uninitialized layer in `%hs` ATUM Neural Network!"), NetworkName)
		return;
	}
	
	LayerTypes.Add(Name, LayerObject->StaticClass());
	LayerObjects.Add(LayerObject);
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
	
	for (UObject* const LayerObject : LayerObjects)
	{
		bHasActualLayers = true;
		if (!Execute_Forward(LayerObject, Subinput, Output))
			return false;
		
		Subinput = Output;
	}
	
	return bHasActualLayers;
}

void UAtumNeuralNetwork::PreEditChange(FProperty* const PropertyAboutToChange)
{
	if (
		PropertyAboutToChange &&
		PropertyAboutToChange->GetFName() == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerTypes)
	)
	{
	    OldLayerTypes.clear();
	    OldLayerTypes.reserve(LayerTypes.Num());
	    for (const TTuple<FName, UClass*>& LayerType : LayerTypes)
	    {
		    OldLayerTypes.push_back(LayerType);
	    }
	}
	
	Super::PreEditChange(PropertyAboutToChange);
}

void UAtumNeuralNetwork::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	if (
		const FProperty* const Property = PropertyChangedEvent.Property;
		Property && Property->GetFName() == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerTypes)
	)
	{
		const int32 ChangedIndex = PropertyChangedEvent.GetArrayIndex(TEXT("LayerTypes"));
		LayerObjects.Reserve(ChangedIndex + 1);
		
		switch (const EPropertyChangeType::Type PropertyChangeType = PropertyChangedEvent.ChangeType)
		{
		case EPropertyChangeType::ArrayAdd:
			LayerObjects.Insert(nullptr, ChangedIndex);
			break;
			
		case EPropertyChangeType::ArrayRemove:
			LayerObjects.RemoveAt(ChangedIndex);
			break;
			
		case EPropertyChangeType::ArrayClear:
			LayerObjects.Empty();
			break;
			
		case EPropertyChangeType::ValueSet:
			OnLayerTypesPropertyChange_ValueSet(ChangedIndex);
			break;
			
		default:
			UE_LOG(LogTemp, Error, TEXT("Property change type %u unaccounted for!"), PropertyChangeType)
		}
	}
	
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}

void UAtumNeuralNetwork::OnLayerTypesPropertyChange_ValueSet(const int32 ChangedIndex) noexcept
{
	const TTuple<FName, UClass*>& OldLayerType = OldLayerTypes[ChangedIndex];
	if (const UClass* const LayerType = LayerTypes[OldLayerType.Key]; LayerType != OldLayerType.Value)
	{
		LayerObjects[ChangedIndex] = LayerType ? NewObject<UObject>(this, LayerType) : nullptr;
	}
}

#undef LOCTEXT_NAMESPACE
