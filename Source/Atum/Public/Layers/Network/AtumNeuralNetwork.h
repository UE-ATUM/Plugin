// © 2023 Kaya Adrian.

#pragma once

#include "AtumNeuralNetworkOptions.h"
#include "Layers/IAtumLayer.h"
#include "Macros/AtumMacrosGuards.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/cloneable.h>
TORCH_INCLUDES_END

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


UCLASS(Blueprintable, BlueprintType, EditInlineNew, DisplayName = "ATUM Neural Network")
class ATUM_API UAtumNeuralNetwork : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumNeuralNetworkOptions, torch::nn::AtumNetwork)
	
#if WITH_EDITOR
	DECLARE_MULTICAST_DELEGATE(FOnPostCDOCompiled);
#endif
	
	UPROPERTY(Transient, NonTransactional, meta = (MustImplement = "/Script/Atum.AtumLayer"))
	mutable TArray<const UObject*> RegisteredLayersConst;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumNeuralNetworkOptions Options;
	
	UPROPERTY(Transient, NonTransactional, VisibleAnywhere, BlueprintGetter = "GetRegisteredLayers", meta = (
		AllowPrivateAccess,
		MustImplement = "/Script/Atum.AtumLayer"
	))
	TArray<TObjectPtr<UObject>> RegisteredLayers;
	
public:
#if WITH_EDITOR
	static const TUniquePtr<FOnPostCDOCompiled> OnPostCDOCompiled;
#endif
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Network", meta = (Keywords = "ATUM Register Layer"))
	FORCEINLINE bool RegisterLayer(const TScriptInterface<IAtumLayer>& Layer) noexcept
	{ return RegisterLayerAt(Layer, RegisteredLayers.Num()); }
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Network", meta = (Keywords = "ATUM Register Layer At Index"))
	bool RegisterLayerAt(const TScriptInterface<IAtumLayer>& Layer, int32 Index = 0) noexcept;
	
	UFUNCTION(BlueprintGetter, Category = "ATUM|Network", CustomThunk, meta = (Keywords = "ATUM Get Registered Layers"))
	UPARAM(meta = (MustImplement = "/Script/Atum.AtumLayer")) const TArray<const UObject*>&
		GetRegisteredLayers() const noexcept;
	
protected:
	virtual void GetParameters_Implementation(
		const UClass* Class,
		TMap<FString, TScriptInterface<IAtumTensor>>& OutValues
	) const noexcept override;
	
#if WITH_EDITOR
	virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;
#endif
	
private:
	DECLARE_FUNCTION(execGetRegisteredLayers) noexcept;
};

#undef LOCTEXT_NAMESPACE
