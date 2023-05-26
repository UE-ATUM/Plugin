// © 2023 Kaya Adrian.

#include "Layers/Network/AtumNeuralNetworkLayers.h"

#include "AtumMacros.h"
#include "AtumSettings.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkLayers"

#if WITH_EDITOR
void UAtumNeuralNetworkLayers::PreEditChange(FProperty* const PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
	
	if (PropertyAboutToChange == nullptr)
		return;
	
	if (
		const FName& PropertyName = PropertyAboutToChange->GetFName();
		PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetworkLayers, LayerTypes)
	)
	{
		OnLayerTypesPropertyChange_SetCachedNetworkIndices();
		PreEditLayerTypes = LayerTypes;
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetworkLayers, LayerObjects))
	{
		PreEditLayerObjects = LayerObjects;
	}
}

void UAtumNeuralNetworkLayers::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
	
	const FProperty* const Property = PropertyChangedEvent.Property;
	if (Property == nullptr)
		return;
	
	if (
		const FName& PropertyName = Property->GetFName();
		PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetworkLayers, LayerTypes)
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
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(UAtumNeuralNetworkLayers, LayerObjects))
	{
		LayerObjects = PreEditLayerObjects;
	}
	
	PreEditLayerTypes.Empty();
	PreEditLayerObjects.Empty();
	CachedIndices.Empty();
}

void UAtumNeuralNetworkLayers::OnLayerTypesPropertyChange_SetCachedNetworkIndices() noexcept
{
	const int32 LayerTypeCount = LayerTypes.Num();
	CachedIndices.Empty(LayerTypeCount);
	
	for (int32 Index = 0; Index < LayerTypeCount; ++Index)
	{
		if (const TObjectPtr<const UClass> LayerType = LayerTypes[Index]; LayerType)
		{
			TTuple<TArray<int32>, int32>& Cache = CachedIndices.FindOrAdd(LayerType);
			Cache.Key.Add(Index);
			Cache.Value = 0;
		}
	}
}

void UAtumNeuralNetworkLayers::OnLayerTypesPropertyChange_ValueSet(const int32 Index) noexcept
{
	if (const UClass* const LayerType = LayerTypes[Index].Get(); LIKELY(LayerType != PreEditLayerTypes[Index]))
	{
		LayerObjects[Index] = LayerType ? NewObject<UObject>(this, LayerType) : nullptr;
	}
}

void UAtumNeuralNetworkLayers::OnLayerTypesPropertyChange_ArrayMove() noexcept
{
	PreEditLayerObjects = LayerObjects;
	
	const int32 LayerTypeCount = LayerTypes.Num();
	for (int32 Index = 0; Index < LayerTypeCount; ++Index)
	{
		TObjectPtr<UObject>& LayerObject = LayerObjects[Index];
		if (const TObjectPtr<const UClass> LayerType = LayerTypes[Index]; LayerType)
		{
			TTuple<TArray<int32>, int32>& Cache = CachedIndices.FindChecked(LayerType);
			LayerObject = PreEditLayerObjects[Cache.Key[Cache.Value++]];
		}
		else
		{
			LayerObject = nullptr;
		}
	}
}
#endif

#undef LOCTEXT_NAMESPACE
