// © 2023 Kaya Adrian.

#include "Layers/Network/AtumNeuralNetworkLayers.h"

#include "Layers/IAtumLayer.h"
#include "Macros/AtumMacrosLog.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkLayers"

const TArray<const UClass*>& UAtumNeuralNetworkLayers::GetLayerTypes() const noexcept
{
	LayerTypesConst.Empty(LayerTypes.Num());
	for (const TObjectPtr<const UClass> LayerType : LayerTypes)
	{
		LayerTypesConst.Add(DuplicateObject<const UClass>(LayerType, GetTransientPackage()));
	}
	return LayerTypesConst;
}

const TArray<const UObject*>& UAtumNeuralNetworkLayers::GetLayerObjects() const noexcept
{
	LayerObjectsConst.Empty(LayerObjects.Num());
	for (const TObjectPtr<UObject> LayerObject : LayerObjects)
	{
		if (const UObject* const Layer = LayerObject.Get(); Layer)
		{
			TScriptInterface<IAtumLayer> DuplicateLayer;
			IAtumLayer::Execute_CloneData(Layer, DuplicateLayer, GetTransientPackage());
			LayerObjectsConst.Add(DuplicateLayer.GetObject());
		}
		else
		{
			LayerObjectsConst.Add(nullptr);
		}
	}
	return LayerObjectsConst;
}

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

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
void UAtumNeuralNetworkLayers::execGetLayerTypes(
	UObject* const Context,
	FFrame& Stack,
	void* const Z_Param__Result
) noexcept
{
	P_FINISH
	
	P_NATIVE_BEGIN
	*static_cast<TArray<const UClass*>*>(Z_Param__Result) = P_THIS->GetLayerTypes();
	P_NATIVE_END
}

void UAtumNeuralNetworkLayers::execGetLayerObjects(
	UObject* const Context,
	FFrame& Stack,
	void* const Z_Param__Result
) noexcept
{
	P_FINISH
	
	P_NATIVE_BEGIN
	*static_cast<TArray<const UObject*>*>(Z_Param__Result) = P_THIS->GetLayerObjects();
	P_NATIVE_END
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning

#undef LOCTEXT_NAMESPACE
