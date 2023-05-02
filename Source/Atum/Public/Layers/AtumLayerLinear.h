// © 2023 Kaya Adrian.

#pragma once

#include "IAtumLayer.h"

#include "AtumLayerLinear.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Linear Options")
struct ATUM_API FAtumOptionsLinear
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	int64 InFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	int64 OutFeatures;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options")
	bool bBias;

	UE_NODISCARD_CTOR
	FAtumOptionsLinear() noexcept;
	
	UE_NODISCARD
	explicit operator torch::nn::LinearOptions() const noexcept;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Linear Layer")
class ATUM_API UAtumLayerLinear : public UObject, public IAtumLayer, public TAtumLayer<torch::nn::LinearImpl>
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumOptionsLinear Options;

protected:
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
