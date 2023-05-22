// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "IAtumLayer.h"

LIBTORCH_INCLUDES_START
#include "torch/nn/cloneable.h"
LIBTORCH_INCLUDES_END

#include "AtumNeuralNetwork.generated.h"

class IAtumTensor;


#define LOCTEXT_NAMESPACE "AtumNeuralNetwork"

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	class AtumNetworkImpl : public Cloneable<AtumNetworkImpl>
	{
	public:
		UE_NODISCARD
		// ReSharper disable once CppMemberFunctionMayBeStatic
		FORCEINLINE Tensor forward(const Tensor& Input) { return Input; }

		virtual void reset() override;
		virtual void pretty_print(std::ostream& stream) const override;
	};
	
	TORCH_MODULE(AtumNetwork);
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Neural Network")
class ATUM_API UAtumNeuralNetwork : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::AtumNetwork)
	
	std::vector<TTuple<FName, UClass*>> OldLayerTypes;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Network", meta = (AllowPrivateAccess))
	FName NetworkLayerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Network", meta = (
		AllowPrivateAccess,
		MustImplement = "/Script/Atum.AtumLayer"
	))
	TMap<FName, UClass*> LayerTypes;
	
	UPROPERTY(Instanced, EditFixedSize, VisibleAnywhere, BlueprintReadOnly, Category = "ATUM|Network", meta = (
		AllowPrivateAccess
	))
	TArray<UObject*> LayerObjects;
	
public:
	UE_NODISCARD_CTOR
	UAtumNeuralNetwork() noexcept;
	
	UFUNCTION(BlueprintCallable)
	void RegisterLayer(FName Name, const TScriptInterface<IAtumLayer>& Layer) noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
	
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
	
private:
	void OnLayerTypesPropertyChange_ValueSet(int32 ChangedIndex) noexcept;
	
public:
	UE_NODISCARD
	FORCEINLINE const TMap<FName, UClass*>& GetLayerTypes() const noexcept { return LayerTypes; }
	
	UE_NODISCARD
	FORCEINLINE const TArray<UObject*>& GetLayerObjects() const noexcept { return LayerObjects; }
};

#undef LOCTEXT_NAMESPACE
