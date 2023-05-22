// © 2023 Kaya Adrian.

#include "Layers/AtumNeuralNetwork.h"

#include "AtumSettings.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetwork"

namespace
{
	class UAtumLayerClass : public UClass
	{
	public:
		mutable int32 CurrentIndex = 0;
		std::vector<int32> CachedNetworkIndices;
	};
}

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

void UAtumNeuralNetwork::RegisterLayer(const TScriptInterface<IAtumLayer>& Layer) noexcept
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
	
	LayerTypes.Add(LayerObject->StaticClass());
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
	do
	{
		if (PropertyAboutToChange == nullptr)
			break;

		if (
			const FName& PropertyName = PropertyAboutToChange->GetFName();
			PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerTypes)
		)
		{
			OnLayerTypesPropertyChange_SetCachedNetworkIndices();
			OldLayerTypes = LayerTypes;
		}
		else if (PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerObjects))
		{
			OldLayerObjects = LayerObjects;
		}
	} while (false);
	
	Super::PreEditChange(PropertyAboutToChange);
}

void UAtumNeuralNetwork::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	do
	{
		const FProperty* const Property = PropertyChangedEvent.Property;
		if (Property == nullptr)
			break;
		
		if (
			const FName& PropertyName = Property->GetFName();
			PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerTypes)
		)
		{
			const int32 Index = PropertyChangedEvent.GetArrayIndex(TEXT("LayerTypes"));
			LayerObjects.Reserve(Index + 1);
			
			switch (const EPropertyChangeType::Type PropertyChangeType = PropertyChangedEvent.ChangeType)
			{
			case EPropertyChangeType::ArrayAdd:
				LayerObjects.Insert(nullptr, Index);
				break;
				
			case EPropertyChangeType::ArrayRemove:
				LayerObjects.RemoveAt(Index);
				break;
				
			case EPropertyChangeType::ArrayClear:
				LayerObjects.Empty();
				break;
				
			case EPropertyChangeType::ValueSet:
				OnLayerTypesPropertyChange_ValueSet(Index);
				break;
				
			case EPropertyChangeType::Duplicate:
				LayerObjects.Insert(DuplicateObject<UObject>(LayerObjects[Index], this), Index + 1);
				break;
				
			case EPropertyChangeType::ArrayMove:
				OnLayerTypesPropertyChange_ArrayMove();
				break;
				
			default:
				ATUM_LOG(Error, TEXT("Property change type %u unaccounted for!"), PropertyChangeType)
			}

			OnLayerTypesPropertyChange_SetCachedNetworkIndices();
		}
		else if (PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerObjects))
		{
			LayerObjects = OldLayerObjects;
		}
	} while (false);
	
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}

void UAtumNeuralNetwork::OnLayerTypesPropertyChange_ValueSet(const int32 Index) noexcept
{
	if (const UClass* const LayerType = LayerTypes[Index]; LIKELY(LayerType != OldLayerTypes[Index]))
	{
		LayerObjects[Index] = LayerType ? NewObject<UObject>(this, LayerType) : nullptr;
	}
}

void UAtumNeuralNetwork::OnLayerTypesPropertyChange_ArrayMove() noexcept
{
	OldLayerObjects = LayerObjects;
	
	const int32 LayerTypeCount = LayerTypes.Num();
	for (int32 Index = 0; Index < LayerTypeCount; ++Index)
	{
		auto* const LayerType = static_cast<const UAtumLayerClass*>(LayerTypes[Index]);
		if (LayerType == nullptr)
		{
			LayerObjects[Index] = nullptr;
			continue;
		}
		
		LayerObjects[Index] = OldLayerObjects[LayerType->CachedNetworkIndices[LayerType->CurrentIndex++]];
	}
}

void UAtumNeuralNetwork::OnLayerTypesPropertyChange_SetCachedNetworkIndices() noexcept
{
	const int32 LayerTypeCount = LayerTypes.Num();
	for (int32 Index = 0; Index < LayerTypeCount; ++Index)
	{
		if (auto* const LayerType = static_cast<UAtumLayerClass*>(LayerTypes[Index]); LayerType)
		{
			LayerType->CurrentIndex = 0;
			LayerType->CachedNetworkIndices.clear();
		}
	}
	for (int32 Index = 0; Index < LayerTypeCount; ++Index)
	{
		if (UClass* const LayerType = LayerTypes[Index]; LayerType)
		{
			static_cast<UAtumLayerClass*>(LayerType)->CachedNetworkIndices.push_back(Index);
		}
	}
}

#undef LOCTEXT_NAMESPACE
