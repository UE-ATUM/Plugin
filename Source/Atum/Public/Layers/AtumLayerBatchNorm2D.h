// © 2023 Kaya Adrian.

#pragma once

#include "IAtumLayer.h"

#include "AtumLayerBatchNorm2D.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Batch Norm 2D Layer")
class ATUM_API UAtumLayerBatchNorm2D : public UObject, public IAtumLayer, public TAtumLayer<torch::nn::BatchNorm2dImpl>
{
	GENERATED_BODY()
};
