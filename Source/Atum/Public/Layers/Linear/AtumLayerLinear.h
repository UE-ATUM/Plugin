// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLinearOptions.h"
#include "Layers/IAtumLayer.h"

#include "AtumLayerLinear.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Linear Layer")
class ATUM_API UAtumLayerLinear : public UObject, public IAtumLayer, public TAtumLayer<torch::nn::LinearImpl>
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumOptionsLinear Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumOptionsLinear& GetOptions() const noexcept { return Options; }

	UE_NODISCARD
	FORCEINLINE FAtumOptionsLinear& GetOptions() noexcept { return Options; }
};
