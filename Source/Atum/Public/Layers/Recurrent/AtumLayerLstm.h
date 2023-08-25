// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerLstmOptions.h"
#include "Layers/IAtumLayer.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/rnn.h>
TORCH_INCLUDES_END

#include "AtumLayerLstm.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLstm"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM LSTM Layer")
class ATUM_API UAtumLayerLstm : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLayerLstmOptions, torch::nn::LSTM)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerLstmOptions Options;
	
	TSharedPtr<std::tuple<at::Tensor, at::Tensor>> HiddenLayer;
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerLstm() noexcept;
};

#undef LOCTEXT_NAMESPACE
