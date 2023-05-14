// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

#include "IAtumLayerBaseActivation.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Activation Layer Base")
class UAtumLayerBaseActivation : public UAtumLayer
{
	GENERATED_BODY()
};

class ATUM_API IAtumLayerBaseActivation : public IAtumLayer
{
	GENERATED_BODY()
};
