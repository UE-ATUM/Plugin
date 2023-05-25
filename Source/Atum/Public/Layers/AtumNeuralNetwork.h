// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "AtumNeuralNetworkOptions.h"
#include "IAtumLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/cloneable.h>
LIBTORCH_INCLUDES_END

#include "AtumNeuralNetwork.generated.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetwork"

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	class AtumNetworkImpl : public Cloneable<AtumNetworkImpl>
	{
	public:
		AtumNetworkOptions options;
		
		UE_NODISCARD_CTOR
		explicit AtumNetworkImpl(const AtumNetworkOptions& options_) noexcept;
		
		UE_NODISCARD
		// ReSharper disable once CppMemberFunctionMayBeStatic
		FORCEINLINE Tensor forward(const Tensor& input) { return input; }
		
		virtual void reset() override;
		virtual void pretty_print(std::ostream& stream) const override;
	};
	
	TORCH_MODULE(AtumNetwork);
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


UCLASS(BlueprintType, DisplayName = "ATUM Neural Network")
class ATUM_API UAtumNeuralNetwork : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::AtumNetwork)
	
#if WITH_EDITORONLY_DATA
	mutable TMap<TObjectPtr<const UClass>, TTuple<TArray<int32>, int32>> CachedNetworkIndices;
	
	UPROPERTY(Transient, NonTransactional)
	mutable TArray<TObjectPtr<const UClass>> PreEditLayerTypes;
	
	UPROPERTY(Transient, NonTransactional)
	mutable TArray<TObjectPtr<UObject>> PreEditLayerObjects;
#endif
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FAtumNeuralNetworkOptions Options;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess, MustImplement = "/Script/Atum.AtumLayer"))
	TArray<TObjectPtr<const UClass>> LayerTypes;
	
	UPROPERTY(Instanced, EditFixedSize, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TArray<TObjectPtr<UObject>> LayerObjects;
	
public:
	UFUNCTION(BlueprintCallable, Category = "ATUM|Network")
	void RegisterLayer(const TScriptInterface<IAtumLayer>& Layer) noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Network")
	UAtumNeuralNetwork* CloneData(UObject* Outer = nullptr, FName Name = NAME_None) const noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
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
