// © 2023 Kaya Adrian.

#pragma once

#include "Engine/DataAsset.h"

#include "AtumNeuralNetworkLayers.generated.h"

class UAtumNeuralNetwork;


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkLayers"

UCLASS(BlueprintType, EditInlineNew, DisplayName = "ATUM Neural Network Layers Data Asset")
class ATUM_API UAtumNeuralNetworkLayers : public UDataAsset
{
	GENERATED_BODY()
	
#if WITH_EDITORONLY_DATA
	mutable TMap<TObjectPtr<const UClass>, TTuple<TArray<int32>, int32>> CachedIndices;
	
	UPROPERTY(Transient, NonTransactional, meta = (MustImplement = "/Script/Atum.AtumLayer"))
	mutable TArray<TObjectPtr<const UClass>> PreEditLayerTypes;
	
	UPROPERTY(Transient, NonTransactional, meta = (MustImplement = "/Script/Atum.AtumLayer"))
	mutable TArray<TObjectPtr<UObject>> PreEditLayerObjects;
#endif
	
	UPROPERTY(Transient, NonTransactional, meta = (MustImplement = "/Script/Atum.AtumLayer"))
	mutable TArray<const UClass*> LayerTypesConst;
	
	UPROPERTY(Transient, NonTransactional, meta = (MustImplement = "/Script/Atum.AtumLayer"))
	mutable TArray<const UObject*> LayerObjectsConst;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintGetter = "GetLayerTypes", meta = (
		AllowPrivateAccess,
		MustImplement = "/Script/Atum.AtumLayer"
	))
	TArray<TObjectPtr<const UClass>> LayerTypes;
	
	UPROPERTY(Instanced, EditFixedSize, VisibleAnywhere, BlueprintGetter = "GetLayerObjects", meta = (
		AllowPrivateAccess,
		MustImplement = "/Script/Atum.AtumLayer"
	))
	TArray<TObjectPtr<UObject>> LayerObjects;
	
public:
	UFUNCTION(BlueprintGetter, Category = "ATUM|Network", CustomThunk, meta = (Keywords = "ATUM Get Layer Types"))
	UPARAM(meta = (MustImplement = "/Script/Atum.AtumLayer")) const TArray<const UClass*>&
		GetLayerTypes() const noexcept;
	
	UFUNCTION(BlueprintGetter, Category = "ATUM|Network", CustomThunk, meta = (Keywords = "ATUM Get Layer Objects"))
	UPARAM(meta = (MustImplement = "/Script/Atum.AtumLayer")) const TArray<const UObject*>&
		GetLayerObjects() const noexcept;
	
protected:
#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
	
	void OnLayerTypesPropertyChange_SetCachedNetworkIndices() noexcept;
	void OnLayerTypesPropertyChange_ValueSet(int32 Index) noexcept;
	void OnLayerTypesPropertyChange_ArrayMove() noexcept;
#endif
	
private:
	DECLARE_FUNCTION(execGetLayerTypes) noexcept;
	DECLARE_FUNCTION(execGetLayerObjects) noexcept;

	friend UAtumNeuralNetwork;
};

#undef LOCTEXT_NAMESPACE
