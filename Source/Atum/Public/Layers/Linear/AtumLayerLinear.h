// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLinearOptions.h"

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
	FAtumLayerLinearOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerLinearOptions& GetOptions() const noexcept { return Options; }

	UE_NODISCARD
	FORCEINLINE FAtumLayerLinearOptions& GetOptions() noexcept { return Options; }
};
