// © 2023 Kaya Adrian.

#pragma once

#include "IAtumLayer.h"

#include "AtumLayerLinear.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Linear Layer")
class ATUM_API UAtumLayerLinear : public UObject, public IAtumLayer, public TAtumLayer<torch::nn::LinearImpl>
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 InFeatures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 OutFeatures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bLearnBias;

public:
	UE_NODISCARD_CTOR
	UAtumLayerLinear() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept override;
};
