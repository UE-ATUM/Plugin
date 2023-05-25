// © 2023 Kaya Adrian.

#include "Layers/AtumNeuralNetwork.h"

#include "AtumSettings.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetwork"

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	AtumNetworkImpl::AtumNetworkImpl(const AtumNetworkOptions& options_) noexcept : options(options_)
	{
	}
	
	void AtumNetworkImpl::reset()
	{
	}
	
	void AtumNetworkImpl::pretty_print(std::ostream& stream) const
	{
		stream << "torch::nn::AtumNetwork";
	}
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning

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

UAtumNeuralNetwork* UAtumNeuralNetwork::CloneData(UObject* const Outer, const FName Name) const noexcept
{
	auto* const NeuralNetwork = NewObject<UAtumNeuralNetwork>(Outer, GetClass(), Name);
	for (TObjectPtr<UObject>& LayerObject : NeuralNetwork->LayerObjects)
	{
		LayerObject = DuplicateObject<UObject>(LayerObject, NeuralNetwork);
	}
	return NeuralNetwork;
}

bool UAtumNeuralNetwork::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry) noexcept
{
	Module.Reset(new torch::nn::AtumNetwork(std::make_shared<torch::nn::AtumNetworkImpl>(
		static_cast<torch::nn::AtumNetworkOptions>(Options)
	)));
	return true;
}

bool UAtumNeuralNetwork::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	bool bHasActualLayers = false;
	TScriptInterface<IAtumTensor> Subinput = Input;
	
	for (const TObjectPtr<UObject> LayerObject : LayerObjects)
	{
		bHasActualLayers = true;
		if (!Execute_Forward(LayerObject.Get(), Subinput, Output))
			return false;
		
		Subinput = Output;
	}
	
	return bHasActualLayers;
}

#if WITH_EDITOR
void UAtumNeuralNetwork::PreEditChange(FProperty* const PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
	
	if (PropertyAboutToChange == nullptr)
		return;
	
	if (
		const FName& PropertyName = PropertyAboutToChange->GetFName();
		PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerTypes)
	)
	{
		OnLayerTypesPropertyChange_SetCachedNetworkIndices();
		PreEditLayerTypes = LayerTypes;
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerObjects))
	{
		PreEditLayerObjects = LayerObjects;
	}
}

void UAtumNeuralNetwork::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
	
	const FProperty* const Property = PropertyChangedEvent.Property;
	if (Property == nullptr)
		return;
	
	if (
		const FName& PropertyName = Property->GetFName();
		PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerTypes)
	)
	{
		const int32 Index = PropertyChangedEvent.GetArrayIndex(TEXT("LayerTypes"));
		const int32 NextIndex = Index + 1;
		
		LayerObjects.Reserve(NextIndex);
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
			LayerObjects.Insert(DuplicateObject<UObject>(LayerObjects[Index], this), NextIndex);
			break;
			
		case EPropertyChangeType::ArrayMove:
			OnLayerTypesPropertyChange_ArrayMove();
			break;
			
		default:
			ATUM_LOG(Error, TEXT("Property change type %u unaccounted for!"), PropertyChangeType)
		}
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetwork, LayerObjects))
	{
		LayerObjects = PreEditLayerObjects;
	}
	
	PreEditLayerTypes.Empty();
	PreEditLayerObjects.Empty();
	CachedNetworkIndices.Empty();
}

void UAtumNeuralNetwork::OnLayerTypesPropertyChange_SetCachedNetworkIndices() noexcept
{
	const int32 LayerTypeCount = LayerTypes.Num();
	CachedNetworkIndices.Empty(LayerTypeCount);
	
	for (int32 Index = 0; Index < LayerTypeCount; ++Index)
	{
		if (const TObjectPtr<const UClass> LayerType = LayerTypes[Index]; LayerType)
		{
			TTuple<TArray<int32>, int32>& CachedIndices = CachedNetworkIndices.FindOrAdd(LayerType);
			CachedIndices.Key.Add(Index);
			CachedIndices.Value = 0;
		}
	}
}

void UAtumNeuralNetwork::OnLayerTypesPropertyChange_ValueSet(const int32 Index) noexcept
{
	if (const UClass* const LayerType = LayerTypes[Index].Get(); LIKELY(LayerType != PreEditLayerTypes[Index]))
	{
		LayerObjects[Index] = LayerType ? NewObject<UObject>(this, LayerType) : nullptr;
	}
}

void UAtumNeuralNetwork::OnLayerTypesPropertyChange_ArrayMove() noexcept
{
	PreEditLayerObjects = LayerObjects;
	
	const int32 LayerTypeCount = LayerTypes.Num();
	for (int32 Index = 0; Index < LayerTypeCount; ++Index)
	{
		TObjectPtr<UObject>& LayerObject = LayerObjects[Index];
		if (const TObjectPtr<const UClass> LayerType = LayerTypes[Index]; LayerType)
		{
			TTuple<TArray<int32>, int32>& CachedIndices = CachedNetworkIndices.FindChecked(LayerType);
			LayerObject = PreEditLayerObjects[CachedIndices.Key[CachedIndices.Value++]];
		}
		else
		{
			LayerObject = nullptr;
		}
	}
}
#endif

#undef LOCTEXT_NAMESPACE
