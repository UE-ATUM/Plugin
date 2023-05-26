// © 2023 Kaya Adrian.

#pragma once

#include "Engine/DataAsset.h"

#include "AtumNeuralNetworkLayers.generated.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkLayers"

UCLASS(BlueprintType, DisplayName = "ATUM Neural Network Layers Data Asset")
class ATUM_API UAtumNeuralNetworkLayers : public UDataAsset
{
	GENERATED_BODY()

#if WITH_EDITORONLY_DATA
	mutable TMap<TObjectPtr<const UClass>, TTuple<TArray<int32>, int32>> CachedIndices;
	
	UPROPERTY(Transient, NonTransactional)
	mutable TArray<TObjectPtr<const UClass>> PreEditLayerTypes;
	
	UPROPERTY(Transient, NonTransactional)
	mutable TArray<TObjectPtr<UObject>> PreEditLayerObjects;
#endif

protected:
	UPROPERTY(EditAnywhere, meta = (MustImplement = "/Script/Atum.AtumLayer"))
	TArray<TObjectPtr<const UClass>> LayerTypes;
	
	UPROPERTY(Instanced, EditFixedSize, VisibleAnywhere)
	TArray<TObjectPtr<UObject>> LayerObjects;
	
#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
	
	void OnLayerTypesPropertyChange_SetCachedNetworkIndices() noexcept;
	void OnLayerTypesPropertyChange_ValueSet(int32 Index) noexcept;
	void OnLayerTypesPropertyChange_ArrayMove() noexcept;
#endif
	
public:
	UE_NODISCARD
	FORCEINLINE const TArray<TObjectPtr<const UClass>>& GetLayerTypes() const noexcept { return LayerTypes; }
	
	UE_NODISCARD
	FORCEINLINE void GetLayerObjects(TArray<TObjectPtr<const UObject>>& OutValue) const noexcept
	{ OutValue = TArray<TObjectPtr<const UObject>>(LayerObjects); }
};

#undef LOCTEXT_NAMESPACE
