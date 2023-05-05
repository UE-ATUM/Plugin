// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

#include "IAtumLayerBaseNorm.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Norm Layer Base")
class UAtumLayerBaseNorm : public UAtumLayer
{
	GENERATED_BODY()
};

class ATUM_API IAtumLayerBaseNorm : public IAtumLayer
{
	GENERATED_BODY()
};
