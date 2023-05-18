// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

LIBTORCH_INCLUDES_START
#include "torch/nn/cloneable.h"
LIBTORCH_INCLUDES_END

#include "AtumNeuralNetwork.generated.h"


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
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Network", meta = (AllowPrivateAccess))
	TMap<FName, TScriptInterface<IAtumLayer>> NamedLayers;
	
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
	
public:
	UE_NODISCARD
	FORCEINLINE const TMap<FName, TScriptInterface<IAtumLayer>>& GetNamedLayers() const noexcept { return NamedLayers; }
	
	UE_NODISCARD
	FORCEINLINE TMap<FName, TScriptInterface<IAtumLayer>>& GetNamedLayers() noexcept { return NamedLayers; }
};
