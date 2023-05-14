// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

#include "IAtumLayerBaseNormalization.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Normalization Layer Base")
class UAtumLayerBaseNormalization : public UAtumLayer
{
	GENERATED_BODY()
};

class ATUM_API IAtumLayerBaseNormalization : public IAtumLayer
{
	GENERATED_BODY()
};
